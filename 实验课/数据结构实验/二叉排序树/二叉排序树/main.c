#include <stdio.h>
typedef int DataType;
#include "tree.h"

void DestroyBinaryTree(BinaryTree tree);
void visit(int data);
int compare(int a, int b);
BinaryTree InsertNode(BinaryTree tree, DataType node, int (*compare)(DataType, DataType));

int main()
{
    int a;
    BinaryTree tree = NULL;
    printf("请输入数据：\n");
    scanf("%d", &a);
    while(a)
    {
        tree = InsertNode(tree, a, compare);
        scanf("%d", &a);
    }
    printf("中序遍历结果为：\n");
    InOrder(tree, visit);
    putchar('\n');
    DestroyBinaryTree(tree);
    return 0;
}
//第二个参数提供一个比较两个结点元素的函数compare(a,b)，若a>b返回正数，若a<b返回负数，若a=b返回0
BinaryTree InsertNode(BinaryTree tree, DataType node, int (*compare)(DataType, DataType))
{
    if(tree == NULL)
    {
        BinaryTree Node = (BinaryTree)malloc(sizeof(BinaryTree));
        Node->lson = NULL;
        Node->rson = NULL;
        Node->data = node;
        tree = Node;
    }
    else if(compare(node, tree->data) < 0)
        tree->lson = InsertNode(tree->lson, node, compare);
    else
        tree->rson = InsertNode(tree->rson, node, compare);
    return tree;
}
//上面的函数不使用返回值的写法，用到了指向指针的指针
//void InsertNode(BinaryTree *tree, DataType node, int (*compare)(DataType, DataType))
//{
//    if(*tree == NULL)
//    {
//        BinaryTree Node = (BinaryTree)malloc(sizeof(BinaryTree));
//        Node->lson = NULL;
//        Node->rson = NULL;
//        Node->data = node;
//        *tree = Node;
//    }
//    else if(compare(node, (*tree)->data) < 0)
//        InsertNode(&(*tree)->lson, node, compare);
//    else
//        InsertNode(&(*tree)->rson, node, compare);
//}

void DestroyBinaryTree(BinaryTree tree)
{
    if(tree == NULL) return;
    DestroyBinaryTree(tree->lson);
    DestroyBinaryTree(tree->rson);
    free(tree);
}

void visit(DataType data)
{
    printf("%d ", data);
}

int compare(int a, int b)
{
    return a - b;
}
