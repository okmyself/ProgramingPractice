#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 0
#define OK 1

typedef int Status;

typedef struct node {
    double coef;
    int exp;
    struct node *next;
} Node;

typedef Node* Polynode;

Status addNode(Polynode head, double coef, int exp)
{
    if(head == NULL) return ERROR;
    if(coef == 0) return ERROR;
    Polynode current = head->next, previous = head;
    while(current != NULL)
    {
        //存在这一项
        if(current->exp == exp)
        {
            current->coef += coef;
            //系数为0
            if(current->coef == 0)
            {
                previous->next = current->next;
                free(current);
            }
            return OK;
        }
        else if(current->exp < exp)
            break;
        previous = current;
        current = current->next;
    }
    //不存在这一项，插入一项
    Polynode node = (Node*)malloc(sizeof(Node));
    node->coef = coef;
    node->exp = exp;
    node->next = current;
    previous->next = node;
    return OK;
}

Polynode initPoly()
{
    Polynode head = (Node*)malloc(sizeof(Node));
    head->coef = 0;
    head->exp = 0;
    head->next = NULL;
    return head;
}

void destroyPoly(Polynode head)
{
    Polynode current = head, next = head->next;
    while(next != NULL)
    {
        free(current);
        current = next;
        next = next->next;
    }
}

void printPoly(Polynode head)
{
    Polynode p = head->next;
    double coef; int exp;
    if(p == NULL) printf("0");
    while(p != NULL) {
        coef = p->coef; exp = p->exp;
        if(p != head->next && coef > 0) printf("+");
        if(coef == 1) ;
        else if(coef == -1) printf("-");
        else if(coef == (int)coef) printf("%.0lf", coef);
        else printf("%.2lf", coef);
        if(exp != 0)
        {
            printf("x");
            if(exp != 1) printf("^%d", exp);
        }
        else if(coef == 1 || coef == -1)
            printf("1");
        p = p->next;
    }
}

Polynode copyPoly(Polynode p)
{
    if(p == NULL) return NULL;
    Polynode p1 = initPoly();
    p = p->next;
    while(p != NULL)
    {
        addNode(p1, p->coef, p->exp);
        p = p->next;
    }
    return p1;
}

Polynode addPoly(Polynode A, Polynode B)
{
    if(A == NULL || B == NULL) return NULL;
    Polynode p1 = A->next;
    Polynode p2 = B->next;
    Polynode C = initPoly();
    while(p1 != NULL)
    {
        addNode(C, p1->coef, p1->exp);
        p1 = p1->next;
    }
    while(p2 != NULL)
    {
        addNode(C, p2->coef, p2->exp);
        p2 = p2->next;
    }
    return C;
}

Polynode minusPoly(Polynode A, Polynode B)
{
    if(A == NULL || B == NULL) return NULL;
    Polynode p1 = A->next, p2 = B->next;
    Polynode C = initPoly();
    while(p1 != NULL)
    {
        addNode(C, p1->coef, p1->exp);
        p1 = p1->next;
    }
    while(p2 != NULL)
    {
        addNode(C, -p2->coef, p2->exp);
        p2 = p2->next;
    }
    return C;
}

Polynode multiPoly(Polynode A, Polynode B)
{
    if(A == NULL || B == NULL) return NULL;
    Polynode p1 = A->next, p2 = B->next;
    Polynode C = initPoly();
    while(p1 != NULL)
    {
        p2 = B->next;
        while(p2 != NULL)
        {
            addNode(C, p1->coef * p2->coef, p1->exp + p2->exp);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return C;
}

Polynode dividePoly(Polynode A, Polynode B, Polynode *R)
{
    if(A == NULL || B == NULL) return NULL;
    A = copyPoly(A);
    B = copyPoly(B);
    Polynode E = initPoly(), quotient, product, r;  //商、积
    r = initPoly();
    addNode(r, 0, 0);
    double coef; int exp;
    while(A->next != NULL && A->next->exp >= B->next->exp)
    {
        coef = (A->next->coef) / (B->next->coef);
        exp = A->next->exp - B->next->exp;
        addNode(E, coef, exp);
        quotient = initPoly();
        addNode(quotient, coef, exp);
        product = multiPoly(quotient, B);
        destroyPoly(quotient);
        r = minusPoly(A, product);
        destroyPoly(product);
        destroyPoly(A);
        A = r;
    }
    *R = r;
    destroyPoly(B);
    return E;
}

Polynode inputPoly()
{
    int size = 100;   //多项式最大读取字符数100
    char *str = fgets((char*)malloc(size), size, stdin), *temp;
    if(*str != '-')     //如果第一项不是负的，添个+号
    {
        temp = str;
        str = (char*)malloc(size);
        str[0] = '+';
        str[1] = '\0';
        str = strcat(str, temp);
        free(temp);
    }
    int len = (int)strlen(str);
    int offset = 0, readCharCount;
    double coef = 0;
    int exp = 0, n; //n是成功读入的个数
    char s = '\0';  //系数的正负号
    char *c = (char*)malloc(10), *e = (char*)malloc(10), *t = (char*)malloc(10);
    *c = '\0'; *e = '\0'; *t = '\0';
    Polynode p = initPoly();
    while((offset < len - 1) &&
          (n = sscanf(str + offset, "%[+-]%[.0-9]%[^0-9+\n-]%[0-9]", &s, c, t, e)) != -1)
    {
        if(*c == '\0') n = sscanf(str + offset, "%[+-]%[^0-9+\n-]%[0-9]", &s, t, e);
        readCharCount = 1 + (int)strlen(c) + (int)strlen(t) + (int)strlen(e);
//        printf("n=%d,%c%sx^%s,count=%d\n",n,s,c,e,readCharCount);
        if(n != 0)
        {
            coef = 0; exp = 0;
            if(*c != '\0') coef = atof(c);
            else coef = 1;
            if(*e != '\0') exp = atoi(e);
            else if(*c == '\0' || readCharCount == 3) exp = 1;
            else if(readCharCount == 2) exp = 0;
            else return NULL;
            if(s == '-') coef = -coef;
            addNode(p, coef, exp);
        }
        offset += readCharCount;
        s = '\0'; *c = '\0'; *e = '\0'; *t = '\0';
    }
    free(c); free(e); free(t); free(str);
    return p;
}

int main(void)
{
    printf("请输入多项式：A(x)=");
    Polynode A = inputPoly();
    if(A == NULL)
    {
        printf("输入有误!\n");
        exit(0);
    }
    printf("您输入的多项式是：A(x)=");
    printPoly(A);
    printf("\n请输入多项式：B(x)=");
    Polynode B = inputPoly();
    if(B == NULL)
    {
        printf("\n输入有误!");
        exit(0);
    }
    printf("您输入的多项式是：B(x)=");
    printPoly(B);
    Polynode C = addPoly(A, B);
    printf("\nC(x)=A(x)+B(x)=");
    printPoly(C);
    Polynode D = multiPoly(A, B);
    printf("\nD(x)=A(x)*B(x)=");
    printPoly(D);
    printf("\nA(x)=B(x)*E(x)+R(x)\nE(x)=");
    Polynode E, R;
    E = dividePoly(A, B, &R);
    printPoly(E);
    printf("\nR(x)=");
    printPoly(R);
    printf("\n");

    destroyPoly(A);
    destroyPoly(B);
    destroyPoly(C);
    destroyPoly(D);
    return 0;
}

