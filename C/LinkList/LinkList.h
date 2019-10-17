#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1

typedef int Status;
typedef int ElemType;

typedef struct node {
    int coef;
    int exp;
    struct node *next;
} Node;

typedef Node* LinkList;

Status ListInsert(LinkList head, int coef, int exp)
{
    if(coef == 0) return ERROR;
    LinkList node = (Node*)malloc(sizeof(Node));
    node->coef = coef;
    node->exp = exp;
    node->next = NULL;
    
    
    return OK;
}

