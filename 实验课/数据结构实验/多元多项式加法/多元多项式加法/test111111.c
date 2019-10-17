#include <stdio.h>
    //引用传递
void swap( int &x, int &y);
int main()
{
    int a=2,b=3;
    printf("before:实参为a,b\na=%d,地址为%d\nb=%d，地址为%d\n\n",a,&a,b,&b);
    swap(a,b);
    printf("after:实参为a,b\na=%d,地址为%d\nb=%d，地址为%d\n\n",a,&a,b,&b);
    return 0;
}
void swap(int &x,int &y)
{
    int tmp;
    tmp=x;
    x=y;
    y=tmp;
        printf("inside:形参为&x,&y\nx=%d,地址为%d\ny=%d,地址为%d\n\n",x,&x,y,&y);
}