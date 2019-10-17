#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>

#ifndef STACK_INCREMENT
#define STACK_INCREMENT 10              //栈满后每次增加容量
#endif
#ifndef STACK_INIT_SIZE
#define STACK_INIT_SIZE 100             //栈初始化容量
#endif
#define OVERFLOW 1
#define UNDERFLOW 2
#define OK 3

typedef int Status;                     //用一个整数(OVERFLOW、UNDERFLOW、OK)来表示状态

typedef struct {
    Elem *top;
    Elem *base;
    int stacksize;
} SqStack;

Status InitStack(SqStack *S);
Status DestroyStack(SqStack *S, void (*destroy)(Elem*));
Status Push(SqStack *S, Elem e);
Status Pop(SqStack *S, Elem *e);
Status GetTop(SqStack *S, Elem *e);
//long StackLength(SqStack *S);

Status InitStack(SqStack *S)
{
    S->base = (Elem*)malloc(STACK_INIT_SIZE * sizeof(Elem));
    if(!S->base) exit(OVERFLOW);        //分配空间失败
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}
//第二个参数为释放数组前对栈中每个结点的操作函数，一般用在栈中存储指针时对每个指针指向的内存空间进行操作，其他情况请直接传递NULL
Status DestroyStack(SqStack *S, void (*destroy)(Elem*))
{
    while(S->top > S->base)
    {
        S->top--;
        if(destroy) destroy(S->top);
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
    if(S->top == S->base) return UNDERFLOW;
    S->top--;
    *e = *S->top;
    return OK;
}

Status GetTop(SqStack *S, Elem *e)
{
    if(S->top == S->base) return UNDERFLOW;
    *e = *(S->top - 1);
    return OK;
}

#define StackEmpty(S) (StackLength(S) > 0 ? 0 : 1)
#define StackLength(S) ((S)->top - (S)->base)
//long StackLength(SqStack *S)
//{
//    return S->top - S->base;
//}

#endif /* stack_h */
