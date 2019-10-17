#ifndef tree_h
#define tree_h

#include <stdio.h>

typedef struct binaryTree {
    int tag;                    //后序遍历时的标志位，0表示该结点暂不访问，1表示该结点可以访问
    DataType data;
    struct binaryTree *lson;
    struct binaryTree *rson;
} *BinaryTree;
typedef BinaryTree Elem;
#include "stack.h"

void PreOrder(BinaryTree tree, void (*visit)(DataType));
void InOrder(BinaryTree tree, void (*visit)(DataType));
void PostOrder(BinaryTree tree, void (*visit)(DataType));
void Exchange(BinaryTree tree);
int GetHeight(BinaryTree tree);

void PreOrder(BinaryTree tree, void (*visit)(DataType))
{
    BinaryTree p = tree;
    SqStack stack;
    InitStack(&stack);
    do
    {
        while(p)
        {
            visit(p->data);     //访问根
            Push(&stack, p);
            p = p->lson;        //遍历左子树
        }
        
        if(!StackEmpty(&stack))
        {
            Pop(&stack, &p);    //退栈
            p = p->rson;        //遍历右子树
        }
    } while(!StackEmpty(&stack) || p);
    DestroyStack(&stack, NULL);
}

void InOrder(BinaryTree tree, void (*visit)(DataType))
{
    BinaryTree p = tree;
    SqStack stack;
    InitStack(&stack);
    do
    {
        //遍历左子树
        while (p)
        {
            Push(&stack, p);
            p = p->lson;
        }
        
        if(!StackEmpty(&stack))
        {
            Pop(&stack, &p);    //退栈
            visit(p->data);     //访问根
            p = p->rson;        //遍历右子树
        }
    } while(!StackEmpty(&stack) || p);
    DestroyStack(&stack, NULL);
}

void PostOrder(BinaryTree tree, void (*visit)(DataType))
{
    BinaryTree p = tree;
    SqStack stack;
    InitStack(&stack);
    do
    {
        //遍历左子树
        while(p)
        {
            p->tag = 0;
            Push(&stack, p);
            p = p->lson;
        }
        
        if(!StackEmpty(&stack))
        {
            Pop(&stack, &p);    //退栈
            if(p->tag == 0)
            {
                p->tag = 1;
                Push(&stack, p);
                p = p->rson;    //遍历右子树
            }
            else
            {
                visit(p->data); //访问根
                p = NULL;
            }
        }
    } while(!StackEmpty(&stack) || p);
    DestroyStack(&stack, NULL);
}

void Exchange(BinaryTree tree)
{
    if(tree)
    {
        //交换tree的左右子树
        BinaryTree temp = tree->rson;
        tree->rson = tree->lson;
        tree->lson = temp;
        
        Exchange(tree->lson);
        Exchange(tree->rson);
    }
}

int GetHeight(BinaryTree tree)
{
    int h1, h2, max;
    if(tree)
    {
        h1 = GetHeight(tree->lson);
        h2 = GetHeight(tree->rson);
        max = (h1 > h2) ? h1 : h2;
        return (max + 1);
    }
    else return 0;
}

#endif /* tree_h */

