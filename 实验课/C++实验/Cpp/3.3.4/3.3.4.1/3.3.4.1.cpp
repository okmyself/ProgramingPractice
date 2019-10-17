#include<iostream>
using namespace std;
void swapref(int *p1, int *p2);
void swap(int *p1, int *p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
int main()
{
    cout << "-------------------------------------" << endl;
    int iv1 = 888;
    int *pointer_1;
    pointer_1 = &iv1;
    cout << "iv1        = " << iv1 << endl;
    cout << "*pointer_1 = " << *pointer_1 << endl;
    cout << "&iv1       = " << &iv1 << endl;
    cout << "pointer_1  = " << pointer_1 << endl;

    cout << "-------------------------------------" << endl;
    int iv2 = 666;
    int *pointer_2;
    pointer_2 = &iv2;
    cout << "iv2        = " << iv2 << endl;
    cout << "*pointer_2 = " << *pointer_2 << endl;
    cout << "&iv2       = " << &iv2 << endl;
    cout << "pointer_2  = " << pointer_2 << endl;

    cout << "-------------------------------------" << endl;
    swap(pointer_1, pointer_2); //交换pointer_1、pointer_2指向内存地址存储的指
    cout << "iv1        = " << iv1 << endl;
    cout << "iv2        = " << iv2 << endl;
    cout << "*pointer_1 = " << *pointer_1 << endl;
    cout << "*pointer_2 = " << *pointer_2 << endl;
    cout << "pointer_1  = " << pointer_1 << endl;
    cout << "pointer_2  = " << pointer_2 << endl;
    return 0;
}
