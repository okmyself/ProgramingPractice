#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM_OF_KEY 3                //最高3位数
#define RADIX 10                        //基数
#define succ(i) (i + 1)                 //寻找队列中的后继

typedef int datatype;

typedef struct {
    int key[MAX_NUM_OF_KEY];            //以数组形式保存数字的每一位，key[0]表示最高位（优先级最高）
//    datatype info;                      //保留元素
    int next;                           //静态链表指针
} node;

typedef struct {
    int front;
    int rear;
} elem;

int RadixSort(node *R);

int main(void)
{
    int n, i, j, t;
    //输入
    printf("请输入数字个数：");
    scanf("%d", &n);
    node num[n];
    printf("请依次输入数字（不超过%d位）：\n", MAX_NUM_OF_KEY);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &t);
        for(j = MAX_NUM_OF_KEY - 1; j >= 0; j--)
        {
            num[i].key[j] = t % 10;
            t /= 10;
        }
        num[i].next = i + 1;
    }
    num[i - 1].next = -1;
    
    int P = RadixSort(num);
    //输出
    while(P != -1)
    {
        printf("%d%d%d ", num[P].key[0], num[P].key[1], num[P].key[2]);
        P = num[P].next;
    }
    putchar('\n');
    return 0;
}

int RadixSort(node *R)
{
    int i, j, k, t;
    int P = 0;
    elem *Q = (elem*)calloc(RADIX, sizeof(elem));
    for(i = MAX_NUM_OF_KEY - 1; i >= 0; i--)
    {
        //初始化Q
        for(j = 0; j < RADIX; j++)
        {
            Q[j].front = -1;
            Q[j].rear = -1;
        }
        //分配（distribute）
        while(P != -1)
        {
            k = R[P].key[i];            //进第k个队列
            if(Q[k].front == -1)
                Q[k].front = P;
            else
                R[Q[k].rear].next = P;
            Q[k].rear = P;              //修改队头、队尾指针
            P = R[P].next;              //取当前关键字的下一个元素
        }
        //收集（collect）
        j = 0;
        while(Q[j].front == -1)         //寻找第一个非空队列
            j = succ(j);
        P = Q[j].front;                 //排序后当前关键字的第一个元素
        t = Q[j].rear;                  //第一个非空队列的尾指针
        for(k = succ(j); k < RADIX; k++)
        {
            if(Q[k].front != -1)
            {
                R[t].next = Q[k].front;
                t = Q[k].rear;
            }
            R[t].next = -1;             //静态链表尾
        }
    }
    return P;                           //返回静态链表头指针
}
