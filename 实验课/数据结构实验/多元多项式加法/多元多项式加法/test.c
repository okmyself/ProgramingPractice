//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//
//#define ERROR 0
//#define OK 1
//
//typedef int Status;
//typedef struct PNode
//{
//    int tag;        //标志0，1 。  1代表表节点  2代表原子
//    int exp;       //指数 或 元的个数  或  元的ASCII码
//    union
//    {
//        float coef;  //系数
//        struct PNode *hp;  //table pointer   纵向指针  用来指向 元 相同的情况下同一级的横向下一个链表
//    };
//    struct PNode *tp;   //head pointer  横向指针 用来指向 元 不相同的情况下同一级的纵向下一个链表
//} PNode, *PList;
//
//Status CPList(const PList L, PList *PL);
//
//Status MergeList(PList l1, PList l2);
//
//Status DestroyList(PNode *PN);
//
//Status PRList(const PNode *PN);
//
//Status AddList(const PList L1, const PList L2, PList *PL)
//{//相加 思路:把l2中的东西都装到l1中去 再让 PL 指向l1
//    //输出时：字母后面代表指数，字母前面代表相乘，没有逗号隔开的 代表相加
//    PList l1, l2;
//    CPList(L1, &l1);
//    CPList(L2, &l2);   //拷贝操作，原参数因此 不会受影响
//
//    l1->exp = l1->exp > l2->exp ? l1->exp : l2->exp;  //元的个数
//
//    MergeList(l1, l2);
//
//    *PL = l1;
//    free(l2); //释放表头
//
//    return OK;
//}
//
//Status MergeList(PList l1,PList l2)
//{//合并 结果放在l1中
//    PList l1h,l2h,l1t,l2t,l1p,l2p,l1pt,l2pt,lta,ltb,la,lb;
//    l1h=l1->hp;  l2h=l2->hp;
//
//    int flag=0;  //说明横向是否完成   插入与删除的操作下方有说明
//
//
//    //在l1中纵向搜索  是否有与当前 l2的纵向 相匹配的 元
//    for(l1pt=l1,l1p=l1->hp;l1p && l1p->exp!=l2h->exp;l1p=l1p->hp,l1pt=l1pt->hp);
//
//    if(l1p)
//    {
//        l1h=l1p;  //有匹配 则指定下方 要进行横向匹配的 l1的纵向
//        if(l2->hp->hp)
//        {MergeList(l1,l2->hp);}  //再寻找纵向匹配
//    }
//    if(!l1p)
//    {//若 纵向 没有匹配
//        //在 当前纵向的最后一个节点插入 该l2的纵向节点
//        l2->hp=l2h->hp;
//        l2h->hp=l1pt->hp;
//        l1pt->hp=l2h;
//        if(l2->hp)
//        {MergeList(l1,l2);}  //再寻找纵向匹配
//    }
//    else{ //若纵向匹配 则按上方指定的纵向 进行它们横向的匹配  穿插
//        for(l1t=l1h,la=l1h->tp;la;la=la->tp,l1t=l1t->tp)  //遍历比较 两个表的横向
//        {
//            for(l2t=l2h,lb=l2h->tp;lb;lb=lb->tp,l2t=l2t->tp)
//            {
//                if(la->exp == lb->exp)     //判断指数若相同
//                {//下面的操作把l2在该横向中与l1指数相同的节点 插入到l1中 并删除 l2中该节点的位置
//                    flag=1;  //说明下方会完成 插入与删除的操作
//                    if(la->tag==0 && lb->tag==0)
//                    {
//                        la->coef += lb->coef;
//
//                        ltb=lb->tp;   //做保留
//                        l2t->tp=ltb;  //在l2中删除节点lb
//                        free(lb);
//
//                        break;
//                    }
//
//                    if(la->tag==0 && lb->tag==1)
//                    {
//                        lta=la->tp;    //做保留
//                        la->tp=lb->hp->tp;  //在l2中插入节点 la
//                        lb->hp->tp=la;
//                        la->exp=0;
//
//                        ltb=lb->tp;   //做保留
//                        l1t->tp=lb;   //把lb插入l1 并覆盖 原la节点位置
//                        la=lb;
//                        lb->tp=lta;
//
//                        l2t->tp=ltb;  //在l2中删除节点lb
//
//                        break;
//                    }
//
//                    if(la->tag==1 && lb->tag==0)
//                    {
//                        ltb=lb->tp;   //做保留
//                        lb->tp=la->hp->tp;  //在l1中插入lb 节点
//                        la->hp->tp=lb;
//                        lb->exp=0;
//
//                        l2t->tp=ltb;  //在l2中删除节点lb
//
//                        break;
//                    }
//                    //递归  la->hp  lb->hp
//                    //若都为子表的情况
//                    MergeList(la,lb);
//                    flag=0;     //直接递归 因此未进行表连接
//                    l2t->tp=lb->tp;   //删除横向的相同节点
//                    free(lb);
//                    break;
//
//                }
//
//            }
//
//        }
//
//        if(!flag)  //若未进入表之间的相互连接  则手动连接
//        {l1t->tp=l2h->tp;}   //用表l1在该横向的最后一个节点 连接表l2在该横向的首节点
//        flag=0;
//    }
//    return OK;
//}
//
//Status CPList(const PList L, PList *PL)   //copy list
//{
//    if (!((*PL) = (PList) malloc(sizeof(PNode)))) return ERROR;
//    (*PL)->exp = L->exp;
//    (*PL)->tag = L->tag;
//
//
//    if (L->tag == 0)
//    {
//        (*PL)->coef = L->coef;
//    }
//    else if (L->hp)
//    {
//        CPList(L->hp, &(*PL)->hp);
//    }
//    else
//    {
//        (*PL)->hp = NULL;
//    }
//
//    if (L->tp)
//    {
//        CPList(L->tp, &(*PL)->tp);
//    }
//    else
//    {
//        (*PL)->tp = NULL;
//    }
//    return OK;
//}
//
//Status MKNode(PList *PLi, float coef, int num, ...)  //num代表有多少元  ...输入顺序按照 元，指数
//{
//    PList *PL;
//    PNode *pn1, *pnt;
//    PL = &pnt;
//    va_list ap;
//    va_start(ap, num);
//    int i;
//    for (i = 1; i <= num; i++)
//    {//创建添加 表信息
//        if (!((*PL) = (PList) malloc(sizeof(PNode)))) return ERROR;    //头表
//        if (!((pn1) = (PList) malloc(sizeof(PNode)))) return ERROR;
//        (*PL)->exp = va_arg(ap, int);
//        (*PL)->tag = 1;//1代表表节点
//        (*PL)->tp = pn1;//横向
//        pn1->exp = va_arg(ap, int);
//        pn1->tp = NULL;//横向
//        (*PL)->hp = NULL;//纵向
//        if (i < num)
//        {
//            pn1->tag = 1;//1代表表节点
//            PL = &pn1->hp;//纵向
//        }
//        else
//        {
//            pn1->tag = 0;//0代表原子节点
//            pn1->coef = coef;
//        }
//
//    }
//    va_end(ap);
//
//    if (!((*PLi) = (PList) malloc(sizeof(PNode)))) return ERROR;
//    (*PLi)->tag = 1;
//    (*PLi)->exp = num;
//    (*PLi)->tp = NULL;
//    (*PLi)->hp = (pnt);  //初始化 头表
//    return OK;
//}
//
//Status PRList(const PNode *PN)
//{    //输出时：字母后面代表指数，字母前面代表相乘，没有逗号隔开的 代表相加
//    PNode *tp = NULL;
//    PNode *hp = NULL;
//    if (PN->hp)  //如果 PN不为空
//    {
//        hp = PN->hp;//纵向
//        tp = hp->tp;//横向
//    }
//
//    while (tp)
//    {
//        if (tp->tag == 0)
//        {
//            printf("(%.1f,%c,%d)", tp->coef, hp->exp, tp->exp);
//        }
//        else
//        {
//            printf("(");
//            PRList(tp);
//            printf(",%c,%d)", hp->exp, tp->exp);
//        }
//        tp = tp->tp;
//    }
//    if (hp->hp)
//    {
//        PRList(hp);
//    }
//
//    return OK;
//}
//
//Status DestroyList(PNode *PN)
//{
//    PNode *hp = PN;
//    PNode *tp = hp->tp;
//    PNode *dt, *ht;
//
//
//    while (tp)
//    {//横向节点遍历
//        if (tp->tag == 1)
//        {//tag等于1说明它有纵向子节点
//            DestroyList(tp->hp);
//        }
//        dt = tp;
//        tp = tp->tp;
//        free(dt);
//        dt = NULL;
//    }
//    ht = hp;
//    hp = hp->hp;  //删除当前纵向节点
//    free(ht);
//    ht = NULL;
//
//    if (hp)
//    {//纵向节点不为空 继续递归
//        DestroyList(hp);
//    }
//
//
//    return OK;
//}
//
//int main()
//{
//    PList L1, L1a, L1b, L1c, lv1a;
//    PList L2a, L2b, L2c, lv2a, lv3a;
//    MKNode(&L1, 4, 4, 'q', 4, 'b', 2, 'd', 4, 'e', 5);
//    MKNode(&L1a, 7.0, 4, 'n', 2, 'b', 3, 'd', 4, 'f', 6);
//    MKNode(&L1b, 7.0, 6, 'z', 4, 'b', 2, 'd', 4, 'f', 6, 'g', 7, 'r', 8);
//    MKNode(&L1c, 8.0, 4, 'y', 4, 'b', 2, 'd', 4, 'f', 6);
//
//    MKNode(&L2a, 7.0, 4, 'x', 4, 'b', 2, 'd', 4, 'f', 6);
//    MKNode(&L2b, 5.0, 4, 'y', 4, 'b', 2, 'd', 4, 'f', 6);
//    MKNode(&L2c, 7.0, 4, 'z', 4, 'b', 2, 'd', 4, 'f', 6);
//
//    AddList(L2a, L2b, &lv2a);
//    AddList(L2c, lv2a, &lv2a);
//    printf("lv2a = \n");
//    PRList(lv2a);
//
//    AddList(L1, L1a, &lv1a);
//    AddList(lv1a, L1b, &lv1a);
//    AddList(lv1a, L1c, &lv1a);
//    printf("\n\nlv1a = \n");
//    PRList(lv1a);
//
//    AddList(lv2a, lv1a, &lv3a);
//    printf("\n\nlv3a = lv1a + lv2a = \n");
//    PRList(lv3a);
//    putchar('\n');
//
//    DestroyList(lv2a);
//    DestroyList(lv1a);
//    DestroyList(lv3a);
//
//    return OK;
//}
