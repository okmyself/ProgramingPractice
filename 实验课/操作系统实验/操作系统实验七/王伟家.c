#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define INVALID -1
#define total_instruction 320 //指令流长
#define total_vp 32           //页长
#define clear_period 50
typedef struct //页面结构
{
    int pn,      //页面序号
        pfn,     //页面所在内存区的页框号
        counter, //单位时间内访问次数
        time;    //上次访问的时间
} pl_type;
pl_type pl[total_vp]; //页面结构数组
struct pfc_struct
{                            //页面控制结构
    int pn,                  //页面号
        pfn;                 //内存区页面的页框号
    struct pfc_struct *next; //页面指针，用于维护内存缓冲区的链式结构
};
typedef struct pfc_struct pfc_type; //主存区页面控制结构别名
pfc_type pfc[total_vp],             //主存区页面控制结构数组
    *freepf_head,                   //主存区页面控制结构的空闲页面头指针
    *busypf_head,                   //主存区页面控制结构的忙页面头指针
    *busypf_tail;                   //主存区页面控制结构的忙页面尾指针
int diseffect;                      //页错误计数器，初次把页面载入主存时也当做页错误
int a[total_instruction];           //随即指令流数组
int page[total_instruction];        //指令对应的页面号
int offset[total_instruction];      //指令所在页面中的偏移量
int initialize(int);                //初始化页面结构数组和页面控制结构数组
int FIFO(int);                      //先进先出算法
int LRU(int);                       //最近最久未使用算法
int CLOCK(int);                     //简单时钟(钟表)算法
int main()
{
    int s; //随机数
    int i;
    srand(10 * getpid()); /*每次运行时进程号不同，用来作为初始化随机数队列的"种子"*/
    s = (int)((float)(total_instruction - 1) * (rand() / (RAND_MAX + 1.0)));
    printf("\n--------rand instructions queue--------\n");
    for (i = 0; i < total_instruction; i += 4) //产生指令队列
    {
        a[i] = s;                                                    //任选一指令访问点m
        a[i + 1] = a[i] + 1;                                         //顺序执行一条指令
        a[i + 2] = (int)((float)a[i] * (rand() / (RAND_MAX + 1.0))); //执行前地址指令m'
        a[i + 3] = a[i + 2] + 1;                                     //顺序执行一条指令
        printf("%6d%6d%6d%6d\n", a[i], a[i + 1], a[i + 2], a[i + 3]);
        s = (int)((float)((total_instruction - 1) - a[i + 2]) * (rand() / (RAND_MAX + 1.0))) + a[i + 2];
    }
    printf("--------------------------------------\n");
    for (i = 0; i < total_instruction; i++) //将指令序列变换成页地址流
    {
        page[i] = a[i] / 10;
        offset[i] = a[i] % 10;
    }
    printf("compare the three methods:");
    printf("\n--------------------------------------\n");
    printf(" Rss\t FIFO\t LRU\t CLOCK\n");
    for (i = 4; i <= 32; i++) //用户内存工作区从4个页面到32个页面
    {
        printf(" %2d \t", i);
        FIFO(i);
        LRU(i);
        CLOCK(i);
        printf("\n");
    }
    return 0;
} //初始化页面结构数组和页面控制结构数组
//total_pf;  用户进程的内存页面数
int initialize(int total_pf)
{
    int i;
    diseffect = 0;
    for (i = 0; i < total_vp; i++)
    {
        pl[i].pn = i;
        pl[i].pfn = INVALID; //置页面所在主存区的帧号为-1.表示该页不在主存中
        pl[i].counter = 0;   //置页面结构中的访问次数为0
        pl[i].time = -1;     //置页面结构中的上次访问的时间为-1
    }
    for (i = 0; i < total_pf - 1; i++)
    {
        pfc[i].next = &pfc[i + 1]; //建立pfc[i-1]和pfc[i]之间的链接
        pfc[i].pfn = i;            //初始化主存区页面的页框号
    }
    pfc[total_pf - 1].next = NULL;
    pfc[total_pf - 1].pfn = total_pf - 1;
    freepf_head = &pfc[0]; //主存区页面控制结构的空闲页面头指针指向pfc[0]
    return 0;
} //最近最久未使用算法
//int total_pf;       用户进程的内存页面数
int LRU(int total_pf)
{
    int MinT;  //最小的访问时间，即很久没被访问过
    int MinPn; //拥有最小的访问时间的页的页号
    int i, j;
    int CurrentTime;      //系统当前时间
    initialize(total_pf); //初始化页面结构数组和页面控制结构数组
    CurrentTime = 0;
    diseffect = 0;
    for (i = 0; i < total_instruction; i++)
    {
        if (pl[page[i]].pfn == INVALID) //页面失效
        {

            diseffect++;             //页错误次数加
            if (freepf_head == NULL) //无空闲页面
            {
                MinT = 100000;
                for (j = 0; j < total_vp; j++)
                { //找出time的最小值，表明该页很久没被访问过
                    if (MinT > pl[j].time && pl[j].pfn != INVALID)
                    {
                        MinT = pl[j].time;
                        MinPn = j;
                    }
                }
                freepf_head = &pfc[pl[MinPn].pfn]; //最久没被访问过的页被释放
                pl[MinPn].pfn = INVALID;           //最久没被访问过的页被换出主存
                pl[MinPn].time = -1;               //最久没被访问过的页的访问时间置为无效
                freepf_head->next = NULL;
            }
            pl[page[i]].pfn = freepf_head->pfn; //有空闲页面,把相应的页面换入主存，并把pfn改为相应的页框号
            pl[page[i]].time = CurrentTime;     //令访问时间为当前系统时间
            freepf_head = freepf_head->next;    //减少一个空闲页面
        }
        else
            pl[page[i]].time = CurrentTime; //命中则刷新该单元的访问时间
        CurrentTime++;                      //系统当前时间加
    }
    printf("%6.3f\t", 1 - (float)diseffect / 320);
    return 0;
} //简单时钟算法
//int total_pf;       用户进程的内存页面数
int CLOCK(int total_pf)
{
    int i;
    int use[total_vp]; //使用位
    int swap;
    swap = 0; //发生替换
    initialize(total_pf);
    pfc_type *pnext; //时钟指针

    pfc_type *head; //队列头指针
    pnext = freepf_head;
    head = freepf_head;
    for (i = 0; i < total_vp; i++)
    {
        use[i] = 0;
    } //初始化使用位为
    diseffect = 0;
    for (i = 0; i < total_instruction; i++)
    {
        if (pl[page[i]].pfn == INVALID) //页面失效,不在主存中
        {
            diseffect++;             //页错误次数加
            if (freepf_head == NULL) //无空闲页面
            {
                while (use[pnext->pfn] == 1) //若时钟指针指向的页的使用位为，则改为并跳过
                {
                    use[pnext->pfn] = 0;
                    pnext = pnext->next;
                    if (pnext == NULL)
                        pnext = head; //如果时钟指针到达队列尾部，重新返回头部
                }                     //换出被替换的页
                pl[pnext->pn].pfn = INVALID;
                swap = 1;
            }
            if (use[pnext->pfn] == 0)
            {                                 //如果使用位为，则换入相应的页
                pl[page[i]].pfn = pnext->pfn; //页面结构中要标记页框号
                pnext->pn = page[i];          //页面控制结构中要标记页号
                use[pnext->pfn] = 1;          //重置使用位为
                pnext = pnext->next;          //时钟指针下移
                if (pnext == NULL)
                    pnext = head; //如果时钟指针到达队列尾部，重新返回头部
                if (swap == 0)
                {
                    freepf_head = freepf_head->next;
                }
            }
        }
        else
        {                             //页面在主存中
            use[pl[page[i]].pfn] = 1; //刷新使用位为
        }
    }
    printf("%6.3f\t", 1 - (float)diseffect / 320);
    return 0;
}

//先进先出算法版本
//int total_pf;       用户进程的内存页面数
//实现细节由CLOCK算法退化而来，与FIFO同效果
int FIFO(int total_pf)
{
    int i;
    int use[total_vp];
    int swap = 0;
    initialize(total_pf);
    pfc_type *pnext, *head;
    pnext = freepf_head;
    head = freepf_head;
    for (i = 0; i < total_vp; i++)
    {
        use[i] = 0;
    }
    diseffect = 0;
    for (i = 0; i < total_instruction; i++)
    {
        if (pl[page[i]].pfn == INVALID) //页面失效,不在主存中
        {
            diseffect++;
            if (freepf_head == NULL) //无空闲页面
            {
                while (use[pnext->pfn] == 1)
                {
                    use[pnext->pfn] = 0;
                    pnext = pnext->next;
                    if (pnext == NULL)
                        pnext = head;
                } //换出被替换的页
                pl[pnext->pn].pfn = INVALID;
                swap = 1;
            }
            if (use[pnext->pfn] == 0)
            {                                 //如果使用位为，则换入相应的页
                pl[page[i]].pfn = pnext->pfn; //页面结构中要标记页框号
                pnext->pn = page[i];          //页面控制结构中要标记页号
                use[pnext->pfn] = 1;          //重置使用位为
                pnext = pnext->next;
                if (pnext == NULL)
                    pnext = head;
                if (swap == 0)
                {
                    freepf_head = freepf_head->next;
                }
            }
        }
    }
    printf("%6.3f\t", 1 - (float)diseffect / 320);
    return 0;
}