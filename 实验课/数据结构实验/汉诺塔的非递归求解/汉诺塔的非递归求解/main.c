#include <stdio.h>
#include <stdlib.h>
#define STACK_INCREMENT 10              //栈满后每次增加容量
#define STACK_INIT_SIZE 100             //栈初始化容量
#define OVERFLOW 1
#define OK 2
#define ERROR 3

typedef int Status;                     //用一个整数(OVERFLOW、OK、ERROR)来表示状态

typedef struct {
    short int label;                    //记录执行到的标记位置
    char from;
    char to;
    char another;
    int n;
    
    char from_before;
    char to_before;
    char another_before;
    int n_before;
} Elem;

typedef struct {
    Elem *top;
    Elem *base;
    int stacksize;
} SqStack;

Status InitStack(SqStack *S);
Status DestroyStack(SqStack *S);
Status Push(SqStack *S, Elem e);
Status Pop(SqStack *S, Elem *e);
Status GetTop(SqStack *S, Elem *e);
void Hanoi(char from, char to, char another, int n);

Status InitStack(SqStack *S)
{
    S->base = (Elem*)malloc(STACK_INIT_SIZE * sizeof(Elem));
    if(!S->base) exit(OVERFLOW);        //分配空间失败
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}
               
Status DestroyStack(SqStack *S)
{
    while(S->top > S->base)
    {
        S->top--;
        free(S->top);
    }
    free(S->base);
    return OK;
}

Status Push(SqStack *S, Elem e)
{
    // 处理栈满问题
    if(S->top - S->base >= S->stacksize) {
        //栈满，追加存储空间
        S->base = (Elem*)realloc(S->base, (S->stacksize + STACK_INCREMENT) * sizeof(Elem));
        if(!S->base) exit(OVERFLOW);
        S->top = S->base + S->stacksize;
        S->stacksize += STACK_INCREMENT;
    }
    *S->top = e;
    S->top++;
    return OK;
}

Status Pop(SqStack *S, Elem *e)
{
    if(S->top == S->base) return ERROR;
    S->top--;
    *e = *S->top;
    return OK;
}

Status GetTop(SqStack *S, Elem *e)
{
    if(S->top == S->base) return ERROR;
    *e = *(S->top - 1);
    return OK;
}

//从from塔座上搬n个圆盘到to塔座上，another是另一个辅助塔座
void Hanoi(char from, char to, char another, int n)
{
    Elem current, temp;
    SqStack s;
    InitStack(&s);
    
    //非递归入口
    current.label = 3;                  //label = 3压在栈底，作为递归出口
    current.n = n;
    current.from = from;
    current.another = another;
    current.to = to;
    
    Push(&s, current);
    
label0:                                 //递归总入口
    GetTop(&s, &temp);
    if (temp.n == 1)                    //递归结束条件
    {
        printf("将第1个圆盘从%c塔座搬到%c塔座\n", temp.from, temp.to);
        goto label3;
    }
    
//    Hanoi(from, another, to, n - 1);
    
    //递归总入口
    //保存进入递归函数之前的数据
    current.label = 1;
    current.n_before = temp.n;
    current.from_before = temp.from;
    current.another_before = temp.another;
    current.to_before = temp.to;
    
    //记录递归参数列表中的数据
    current.n = current.n_before - 1;
    current.from = current.from_before;
    current.another = current.to_before;
    current.to = current.another_before;
    
    Push(&s, current);
    goto label0;
    
label1:                                 //第一个递归语句调用结束，退栈
    Pop(&s, &current);
    
    printf("将第%d个圆盘从%c塔座搬到%c塔座\n", current.n_before, current.from_before, current.to_before);

//    Hanoi(another, to, from, n - 1);
    
    current.label = 2;
    current.from = current.another_before;
    current.another = current.from_before;
    current.to = current.to_before;
    
    Push(&s, current);
    goto label0;
    
label2:                                 //第二个递归语句调用结束，退栈
    Pop(&s, &current);
    
label3:
    GetTop(&s, &temp);
    switch(temp.label)
    {
        case 1: goto label1;
        case 2: goto label2;
        case 3: Pop(&s, &temp);
    }
    DestroyStack(&s);
}

int main()
{
    Hanoi('a', 'c', 'b', 3);
    return 0;
}
