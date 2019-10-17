#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define total_vp 32 // 虚页长
#define total_instruction 320   // 指令流长
#define INVALID -1

int init(int);  // 初始化页结构数组和页控制结构数组
int LRU(int);   // 最近最久未使用算法
int FIFO(int);  // 先进先出算法
int CLOCK(int); // 简单时钟(钟表)算法

typedef struct  // 页结构
{
    int pn, // 页号
        pfn,    // 页所在内存区的页框号
        counter,    // 单位时间内的访问次数
        time;   // 上次访问的时间
} pl_type;
pl_type pl[total_vp];   // 页结构数组

typedef struct pfc_struct   // 页控制结构
{
    int pn, // 页号
        pfn;    // 内存区页的页框号
    struct pfc_struct* next;    // 页指针，用于维护内存缓冲区的链式结构
} pfc_type;
pfc_type pfc[total_vp]; // 主存区页控制结构数组
pfc_type* freepf_head;  // 空闲页头指针
pfc_type* busypf_head;  // 忙页头指针
pfc_type* busypf_tail;  // 忙页尾指针

int diseffect;  // 页错误计数器
int a[total_instruction];   // 随机指令流数组
int page[total_instruction];    // 指令对应的页号
int offset[total_instruction];  // 指令所在页的偏移量

int main() {
    int s, i, j;
    srand(10 * getpid());   // 使用进程号作为初始化随机数队列的种子
    s = (int) ((total_instruction - 1) * (rand() / (RAND_MAX + 1.0f))); // 产生随机数
    // 生成随机指令队列
    printf("-------------生成随机指令序列-------------\n");
    for (i = 0; i < total_instruction; i += 4) {
        a[i] = s;   // 任选一指令访问点m
        a[i + 1] = a[i] + 1;    // 顺序执行一条指令
        a[i + 2] = (int) (a[i] * (rand() / (RAND_MAX + 1.0f)));  // 再任选一指令访问点m'
        a[i + 3] = a[i + 2] + 1;    // 顺序执行一条指令
        printf("%d\t%d\t%d\t%d\n", a[i], a[i + 1], a[i + 2], a[i + 3]);
        s = (int) (total_instruction - 1 - a[i + 2]) * rand() / (RAND_MAX + 1.0f) + a[i + 2];
    }
    // 将指令序列变换成页地址流
    for (i = 0; i < total_instruction; i++) {
        page[i] = a[i] / 10;
        offset[i] = a[i] % 10;
    }
    printf("-------------比较三种置换算法-------------\n");
    printf("Page\tFIFO\tLRU\tCLOCK\n");
    for (i = 4; i <= 32; i++)   // 用户内存工作区从4个页面到32个页面
    {
        printf("%d\t", i);
        FIFO(i);
        LRU(i);
        CLOCK(i);
        putchar('\n');
    }
    return 0;
}

// 初始化相关数据结构(页结构数组和页控制结构数组)
int init(int total_pf)  // 参数为用户进程的内存页面数
{
    int i;
    diseffect = 0;
    for (i = 0; i < total_vp; i++) {
        pl[i].pn = i;
        pl[i].pfn = INVALID;    // 页控制结构中的页号为INVALID(-1)时表示页面不在主存
        pl[i].counter = 0;  // 页结构中的访问次数为0
        pl[i].time = -1;    // 页结构中的上次访问的时间为-1
    }
    for (i = 0; i < total_pf - 1; i++) {
        pfc[i].next = &pfc[i + 1];  // 建立pfc[i]和pfc[i + 1]之间的链接
        pfc[i].pfn = i; // 初始化主存区页的页框号
    }
    pfc[total_pf - 1].next = NULL;
    pfc[total_pf - 1].pfn = total_pf - 1;
    freepf_head = &pfc[0];  // 空闲页头指针指向pfc[0]
    return 0;
}

// 先进先出算法
int FIFO(int total_pf)  // 参数为用户进程的内存页面数
{
    int i;
    pfc_type *p;
    init(total_pf); // 初始化相关数据结构(页结构数组和页控制结构数组)
    busypf_head = busypf_tail = NULL;   // 忙页队列头、尾链接初始化为NULL
    for (i = 0; i < total_instruction; i++) {
        if (pl[page[i]].pfn == INVALID) // 页面失效
        {
            diseffect += 1; // 页错误计数器记录失效次数+1
            if (freepf_head == NULL)    // 无空闲页面
            {
                p = busypf_head->next;
                pl[busypf_head->pn].pfn = INVALID;
                freepf_head = busypf_head;  // 释放忙页队列的第一个页面
                freepf_head->next = NULL;
                busypf_head = p;
            }
            p = freepf_head->next; // 按FIFO方式调新页入内存
            freepf_head->next = NULL;
            freepf_head->pn = page[i];
            pl[page[i]].pfn = freepf_head->pfn;
            if (busypf_tail == NULL)
                busypf_head = busypf_tail = freepf_head;
            else {
                busypf_tail->next = freepf_head;    // 空闲页面-1
                busypf_tail = freepf_head;
            }
            freepf_head = p;
        }
    }
    printf("%f\t", 1 - (float) diseffect / total_instruction);
    return 0;
}

// 最近最久未使用算法
int LRU(int total_pf)   // 参数为用户进程的内存页面数
{
    int i, j;
    int min_time;   // 最小的访问时间，表示很久没被访问过
    int min_page;   // 具有最小访问时间的页号
    int current_time = 0;   // 当前系统时间
    init(total_pf);
    for (i = 0; i < total_instruction; i++) {
        if (pl[page[i]].pfn == INVALID) // 页面失效
        {
            diseffect++;
            if (freepf_head == NULL)    // 无空闲页面
            {
                min_time = RAND_MAX;
                // 找出time的最小值
                for (j = 0; j < total_vp; j++)
                    if (min_time > pl[j].time && pl[j].pfn != INVALID) {
                        min_time = pl[j].time;
                        min_page = j;
                    }
                freepf_head = &pfc[pl[min_page].pfn]; // 空出一个单元
                pl[min_page].pfn = INVALID;
                pl[min_page].time = -1;
                freepf_head->next = NULL;
            }
            pl[page[i]].pfn = freepf_head->pfn; // 有空闲页面，改为有效
            pl[page[i]].time = current_time;
            freepf_head = freepf_head->next;    // 减少一个空闲页面
        } else  // 页面未失效
            pl[page[i]].time = current_time;    // 命中则增加该单元的访问次数
        current_time++;
    }
    printf("%6.4f\t", 1 - (float) diseffect / total_instruction);
    return 0;
}

// 简单时钟算法
int CLOCK(int total_pf) // 参数为用户进程的内存页面数
{
    int i;
    int usage_bit[total_vp];  // 使用位
    int swap = 0;   // 是否发生替换flag
    init(total_pf);
    pfc_type* pnext;    // 时钟指针
    pfc_type* head; // 队列头指针
    pnext = freepf_head;
    head = freepf_head;
    for (i = 0; i < total_vp; i++)
        usage_bit[i] = 0;
    diseffect = 0;  // 初始化使用位为0
    for (i = 0; i < total_instruction; i++) {
        if (pl[page[i]].pfn == INVALID) // 页面失效，不在主存中
        {
            diseffect++;    // 页错误次数加
            if (freepf_head == NULL)    // 无空闲页面
            {
                while (usage_bit[pnext->pfn] == 1)    // 若时钟指针指向的页的使用位为1，则改为并跳过
                {
                    usage_bit[pnext->pfn] = 0;
                    pnext = pnext->next;
                    if (pnext == NULL)
                        pnext = head;   // 如果时钟指针到达队列尾部，重新返回头部
                }   // 换出被替换的页
                pl[pnext->pn].pfn = INVALID;
                swap = 1;
            }
            if (usage_bit[pnext->pfn] == 0)   // 如果使用位为0，则换入相应的页
            {
                pl[page[i]].pfn = pnext->pfn;   // 页面结构中要标记页框号
                pnext->pn = page[i];    // 页面控制结构中要标记页号
                usage_bit[pnext->pfn] = 1;    // 重置使用位为1
                pnext = pnext->next;    // 时钟指针下移
                if (pnext == NULL)
                    pnext = head;   // 如果时钟指针到达队列尾部，重新返回头部
                if (swap == 0)
                    freepf_head = freepf_head->next;
            }
        } else    // 页面在主存中
            usage_bit[pl[page[i]].pfn] = 1;   // 刷新使用位为1
    }
    printf("%f\t", 1 - (float) diseffect / total_instruction);
    return 0;
}
