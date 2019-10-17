#include<iostream>
#include<memory.h>
using namespace std;
void swap1(int *x, int *y)
//通过指针交换实参指针指向内存空间的值
{
    int t = *x;
    *x = *y;
    *y = t;
}

void swap2(int &x, int &y)
//通过引用的别名交换实参的值
{
    int t = x;
    x = y;
    y = t;
}

void swap3(int *x, int *y)
//通过内存拷贝交换实参指针指向内存空间的值
{
    int *t = new int;
    memcpy(t, x, sizeof(int));
    memcpy(x, y, sizeof(int));
    memcpy(y, t, sizeof(int));
    delete t;
}

void swap4(int* &x, int* &y)
//通过引用的指针交换实参指针指向的内存空间的值
{
    int t = *x;
    *x = *y;
    *y = t;
}

int main(void)
{
    int a = 1, b = 2;
    int *pa = &a, *pb = &b;
    cout << "before swap: a=" << a << ", b=" << b << endl;
    swap1(pa, pb);
    cout << "after swap1: a=" << a << ", b=" << b << endl;
    swap2(a, b);
    cout << "after swap2: a=" << a << ", b=" << b << endl;
    swap3(pa, pb);
    cout << "after swap3: a=" << a << ", b=" << b << endl;
    swap4(pa, pb);
    cout << "after swap4: a=" << a << ", b=" << b << endl;
    return 0;
}