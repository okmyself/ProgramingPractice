#include <stdio.h>
typedef int DataType;
#include "tree.h"

void visit(int data);
BinaryTree CreateBinaryTree(void);
void DestroyBinaryTree(BinaryTree tree);

int main(void)
{
    BinaryTree tree;
    printf("按前序建立二叉树，请按顺序输入数字，0表示空\n");
    tree = CreateBinaryTree();
    printf("二叉树的高度为：%d\n", GetHeight(tree));
    Exchange(tree);
    printf("交换左右子树后按前序输出为：\n");
    PreOrder(tree, visit);
    printf("\n按中序输出为：\n");
    InOrder(tree, visit);
    printf("\n按后序输出为：\n");
    PostOrder(tree, visit);
    putchar('\n');
    DestroyBinaryTree(tree);
    return 0;
}

BinaryTree CreateBinaryTree(void)
{
    int a;
    scanf("%d", &a);
    BinaryTree tree = NULL;
    if(a != 0)
    {
        tree = (BinaryTree)malloc(sizeof(struct binaryTree));
        if(!tree) exit(OVERFLOW);
        tree->data = a;
        tree->lson = CreateBinaryTree();
        tree->rson = CreateBinaryTree();
    }
    return tree;
}

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
