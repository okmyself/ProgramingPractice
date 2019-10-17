#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum
{
    ATOM,                               //原子结点（系数为常数的结点）
    LIST                                //表结点（记录变元的表头节点、系数为表的结点）
} ElemTag;

typedef enum
{
    OK, ERROR
} Status;

typedef enum
{
    FALSE, TRUE
} Boolean;

typedef struct MPNode
{
    ElemTag tag;                        //区分原子结点（ATOM）和表结点（LIST）
    int exp;                            //指数域
    union
    {
        //原子结点使用
        float coef;                     //系数域
        //表头结点使用
        char letter;                    //变元字母
        //其它表结点使用
        struct MPNode *hp;              //纵向指针，表结点的表头指针
    };
    struct MPNode *tp;                  //横向指针，相当于线性链表的next，指向下一个元素结点
} MPNode, *MPList;                      //m元多项式广义表类型

Status PrintMPList(const MPList head);
Status DestroyMPList(MPList list);
//参数1为该项的系数，参数2为该项变元的个数，后面num对参数每对代表变元及其指数，变元不允许重复出现
MPList MakeMPNode(float coef, int num, ...);
//复制一份相同的表，复制失败返回NULL
MPList CopyMPList(const MPNode *head);
//务必保证相加的两个多项式的变元顺序均为变元字母从小大排列，否则无法保证结果正确
MPList AddMPList(const MPList L1, const MPList L2);

int main(void)
{
    MPList p = MakeMPNode(5, 2, 'x', 2, 'y', 1);
    PrintMPList(p);
    DestroyMPList(p);
    return 0;
}

Status PrintMPList(const MPList head)
{
    Boolean flag = FALSE;               //表中项的个数是否大于1
    char letter;
    MPList item;
    if (NULL == head) return ERROR;
    letter = head->letter;              //变元字母
    item = head->tp;
    if (NULL != item && NULL != item->tp)
    {
        flag = TRUE;
        putchar('(');
    }
    while (item)
    {
        switch (item->tag)
        {
            case ATOM:
                if (item->coef >= 0) putchar('+');
                if (0 == item->exp)
                    printf("%.2f", item->coef);
                else
                    printf("%.2f%c^%d", item->coef, letter, item->exp);
                break;
            case LIST:
                PrintMPList(item->hp);
                printf("%c^%d", letter, item->exp);
                break;
        }
        item = item->tp;
    }
    if (flag) putchar(')');
    return OK;
}

Status DestroyMPList(MPList list)
{
    MPList item, temp;
    if (NULL == list) return ERROR;

    item = list->tp;
//    //list如果不是头结点，list->hp可能需要销毁
//    if (list->hp != NULL) DestroyMPList(list->hp);
    free(list);                         //释放头结点
    while (NULL != item)
    {
        temp = item;
        item = item->tp;                //处理横向指针指向的下一个结点
        switch (temp->tag)
        {
            case LIST:
                DestroyMPList(temp->hp);
                //fall through
            case ATOM:
                free(temp);             //释放处理过的横向结点
                break;
        }
    }
    return OK;
}
//递归进行多项式中一个结点的创建，为了进行递归声明该函数（可变参数无法直接递归），仅在MakeMPNode函数内部调用
MPList _Recursive_MakeMPNode(float coef, int num, va_list ap)
{
    MPList head, item;
    head = (MPList) malloc(sizeof(MPNode));
    if (NULL == head) return NULL;
    head->tag = LIST;
    //创建多项式的一项时每个表头后（横向指针）仅有一个结点
    item = (MPList) malloc(sizeof(MPNode));
    if (NULL == item)                   //分配失败的处理
    {
        free(head);                     //释放先前开始分配的头结点
        return NULL;
    }
    head->tp = item;
    item->tp = NULL;
    if (0 == num)                       //没有变元的情况（只有一个常数项），存储系数
    {
        item->exp = 0;
        item->tag = ATOM;
        item->coef = coef;
        head->letter = '\0';            //用'\0'字符，方便相加时判断是否只有一个常数项
    }
    else
    {
        item->tag = LIST;
        item->hp = _Recursive_MakeMPNode(coef, num - 1, ap);
        //表头存储变元字母，注意va_arg宏第二个参数不能为char
        head->letter = (char) va_arg(ap, int);
        item->exp = va_arg(ap, int);
        if (NULL == item->hp)           //分配失败，递归进行销毁操作
        {
            DestroyMPList(head);
            head = NULL;
        }
    }
    return head;
}

MPList MakeMPNode(float coef, int num, ...)
{
    MPList head;
    va_list ap;                         //变参列表
    va_start(ap, num);                  //ap指向变参的开头
    head = _Recursive_MakeMPNode(coef, num, ap);
    va_end(ap);
    return head;
}

MPList CopyMPList(const MPNode *head)
{
    MPList first = (MPList) malloc(sizeof(struct MPNode)), pre, cur;
    if (NULL == first) return NULL;     //分配失败
    first->tag = head->tag;
    first->exp = head->exp;
    switch (head->tag)
    {
        case LIST:
            first->hp = CopyMPList(head->hp);
            if (NULL == first->hp)      //子表创建失败，递归销毁
            {
                free(first);
                return NULL;
            }
            break;
        case ATOM:
            first->coef = head->coef;
            break;
    }
    pre = first;
    cur = head->tp;
    while (NULL != head)
    {
        cur = (MPList) malloc(sizeof(struct MPNode));
        if (NULL == cur) return NULL;
        cur->tag = head->tag;
        switch (head->tag)
        {
            case LIST:
                cur->hp = CopyMPList(head->hp);
                if (cur->hp == NULL)    //子表创建失败，递归销毁
                {
                    cur->tp = NULL;
                    DestroyMPList(first);
                    return NULL;
                }
                break;
            case ATOM:
                cur->coef = head->coef;
                break;
        }
        cur->exp = head->exp;
        pre->tp = cur;
        pre = cur;
        head = head->tp;
    }
    cur->tp = NULL;
    return first;
}
//将L2加到L1上，插入后L2会被全部插入L1中，仅在AddMPList函数内部调用
MPList _Recursive_AddMPList(MPList L1, MPList L2)
{
    MPList p1 = L1, p2 = L2, temp;
    if (NULL == L1->tp)                 //L1为空，直接返回L2
    {
        free(L1);
        return L2;
    }
    //合并p1、p2指向的第一行中的常数项（tag=ATOM、exp=0）
    while(NULL != p1)                   //在L1中寻找常数项
    {
        if (ATOM == p1->tag && 0 == p1->exp) break;
        p1 = p1->tp;
    }
    while(NULL != p2)                   //在L1中寻找常数项
    {
        if (ATOM == p2->tag && 0 == p2->exp) break;
        p2 = p2->tp;
    }
    if (NULL != p1 && NULL != p2)       //进行合并
    {
        p1->coef += p2->coef;
        if (p1->coef == 0)              //常数项合并后为0，将其删除
        {
            temp = L1;
            while (p1 != temp->tp) temp = temp->tp;
            temp->tp = NULL;
            free(p1);                   //找到并释放常数项
        }
    }
    else if (NULL == p1 && NULL != p2)
    {
        p1 = L1;
        while (NULL != p1->tp) p1 = p1->tp;
        p1->tp = p2;                    //插在第一行最后一个位置

        temp = L2;
        while (p2 != temp->tp) temp = p2->tp;
        temp->tp = NULL;                //在L2中删除p2此时指向的常数项，防止内存泄漏
    }

    if (NULL == L2->tp)                 //L2为空时直接返回
    {
        free(L2);
        return L1;
    }
    //L1、L2多项式第一行变元相同
    if (p1->letter == p2->letter)
    {
        p1 = L1;
        p2 = L2->tp;                    //注意此时L2中已经没有常数项，且L1->tp和L2->tp均不为NULL
        while (NULL != p1->tp && p1->tp->exp <= p2->exp)
            p1 = p1->tp;
        //循环结束后有两种情况：p2应该加在p1->tp上、p2应该插在p1后
        if (NULL != p1->tp && p1->tp->exp == p2->exp && LIST == p1->tp->tag)
        {
            p1->tp->hp = _Recursive_AddMPList(p1->tp->hp, p2->hp);
            free(p2);
        }
        else
        {
            L2 = p2->tp;
            p2->tp = p1->tp;
            p1->tp = p2;
        }
        //从L2中删除p2后L2为空
        if (NULL == L2->tp)
        {
            free(L2);
            return L1;
        }
        //从L2中删除p2后只剩常数项
        if (ATOM == L2->tp->tag && 0 == L2->tp->exp)
            L2->letter = '\0';
        //从L2中删除p2后只剩tag=LIST、exp=0项
        p2 = L2;
        while (NULL != p2->tp && NULL == p2->tp->tp && LIST == p2->tp->tag && 0 == p2->tp->exp)
        {
            temp = p2;
            p2 = p2->tp->hp;
            free(temp->tp);
            free(temp);
        }
        L2 = p2;
        //TODO: 只剩tag=List、exp=0项以及常数项
        //递归进行L2下一项
        L1 = _Recursive_AddMPList(L1, L2);
    }
    //L1、L2多项式第一行变元不相同
    else
    {
        //比较顺序，将其中变元字母较小的多项式乘以字母较大的变元的0次方
        if (p1->letter < p2->letter)    //将L1插到L2上
            L1 = _Recursive_AddMPList(L2, L1);
        else                            //将L2插到L1上
        {
            p2 = L2;
            //去除L2中全部位于最前面的零系数项
            while (NULL != p2->tp && NULL == p2->tp->tp && LIST == p2->tp->tag && 0 == p2->tp->exp)
            {
                L2 = p2->tp->hp;
                free(p2);
                free(p2->tp);
                p2 = L2;
            }
            //找到要插入的位置
            p1 = L1;
            while (NULL != p1->tp)
            {
                //①p1指向tag=List、exp=0项
                if (LIST == p1->tag && 0 == p1->exp) break;
                //②p1->tp指向常数项，并且不存在tag=LIST、exp=0项
                if (ATOM == p1->tp->tag && 0 == p1->tp->exp) break;
                p1 = L1->tp;
                //③指向最后一项，并且不存在tag=LIST、exp=0项以及常数项，可以和情况②合并
            }
            if (LIST == p1->tag)
                p1->hp = _Recursive_AddMPList(p1->hp, L2);
            else                        //对于情况①以外的情况
            {
                temp = (MPList) malloc(sizeof(struct MPNode));
                temp->tag = LIST;
                temp->exp = 0;
                temp->tp = p1->tp;
                p1->tp = temp;
                p1->hp = L2;
            }
        }
    }
    return L1;
}

MPList AddMPList(const MPList L1, const MPList L2)
{
    //拷贝一份保证原数据不会被破坏
    return _Recursive_AddMPList(CopyMPList(L1), CopyMPList(L2));
}










//输入时请保证字母从括号内到括号外为升序
//MPList Create()
//{
//    double coef;
//    int input, exp;
//    MPList head = (MPList)malloc(sizeof(struct MPNode)), pre, cur;
//    head->tag = LIST;           //表头节点
//    char s[2];
//    printf("请输入变元字母:");
//    scanf("%s", s);
//    head->letter = s[0];
//    //创建变元字母为letter的所有结点
//    printf("%c系数是否为数字？(1.是 2.否 其它.输入结束):", head->letter);
//    scanf("%d", &input);
//    cur = pre = head;
//    while(input == 1 || input == 2)
//    {
//        cur = (MPList)malloc(sizeof(struct MPNode));
//        if(input == 1)
//        {
//            printf("请输入系数和指数:");
//            scanf("%lf%d", &coef, &exp);
//            cur->tag = ATOM;    //原子结点
//            cur->coef = coef;
//            cur->exp = exp;
//        }
//        else
//        {
//            cur->tag = LIST;    //表结点
//            printf("请输入指数:");
//            scanf("%d", &cur->exp);
//            cur->hp = Create(); //创建子表
//        }
//        pre->tp = cur;
//        pre = cur;
//        printf("%c系数是否为数字？(1.是 2.否 其它.输入结束):", head->letter);
//        scanf("%d", &input);
//    }
//    cur->tp = NULL;
//    return head;
//}

//得到多项式的字符串形式，buff为字符串缓存，返回缓存的起始位置
//char* GetString(char *buff, MPList head)
//{
//    int flag = 0;               //表中项的个数是否大于1
//    char *ptr = buff;
//    char letter = head->letter; //变元字母
//    char buffer[BUFF_SIZE];
//    MPList p = head->tp;
//    if(head->tp && head->tp->hp)
//    {
//        flag = 1;
//        *ptr++ = '(';
//    }
//    while(p)
//    {
//        if(p->tag == ATOM)
//        {
//            if(p->coef >= 0) *ptr++ = '+';
//            ptr += sprintf(ptr, "%.2lf%c^%d", p->coef, letter, p->exp);
//        }
//        else
//        {
//            GetString(buffer, p->hp);
//            buff = strcat(buff, buffer);
//            ptr += strlen(buffer);
//            ptr += sprintf(ptr, "%c^%d", letter, p->exp);
//        }
//        p = p->tp;
//    }
//    if(flag) *ptr++ = ')';
//    *ptr = '\0';
//    return buff;
//}
