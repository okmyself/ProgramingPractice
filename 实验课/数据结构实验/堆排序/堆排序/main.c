#include <stdio.h>
#define LeftChild(i) (2 * (i) + 1)
#define RightChild(i) (2 * (i + 1))
#define Parent(i) (((i) - 1) / 2)

void HeapAjust(int arr[], int len, int i);
void HeapSort(int arr[], int len);
void swap(int *a, int *b);
void Print(int arr[], int len);

int main()
{
    int arr[] = { 4, 22, 42, 4 , 53, 43, 44, 3, 45 };
    int len = sizeof(arr) / sizeof(int);
    HeapSort(arr, len);
    Print(arr, len);
    return 0;
}
//堆调整（调整为大根堆）
void HeapAjust(int arr[], int len, int i)
{
    int lchild = LeftChild(i);
    int rchild = RightChild(i);
    int max = i;
   
    if(lchild < len && arr[lchild] > arr[i])
        max = lchild;
    if(rchild < len && arr[rchild] > arr[max])
        max = rchild;
    if(max != i)
    {
        swap(&arr[max], &arr[i]);
        HeapAjust(arr, len, max);
    }
}
//堆排序
void HeapSort(int arr[], int len)
{
    int i;
    //构造初始堆
    for(i = Parent(len - 1); i >= 0; i--)
        HeapAjust(arr, len, i);
    //排序
    for(i = len - 1; i > 0; i--)
    {
        swap(&arr[i], &arr[0]);
        len--;
        HeapAjust(arr, len, 0);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Print(int arr[], int len)
{
    int i;
    for(i = 0; i < len; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}
