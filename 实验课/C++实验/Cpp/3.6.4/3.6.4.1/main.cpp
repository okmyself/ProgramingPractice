#include <iostream>
#include "Shape.h"
using namespace std;

int main()
{
    Circle s0(30, 45, 35);
    s0.print();
    cout << "-----------------------------" << endl;
    Circle s1(50, 89, 23);
    s1.print();
    cout << "-----------------------------" << endl;
    Rectangle s2(30, 53);
    s2.print();
    cout << "-----------------------------" << endl;
    Rectangle s3(28, 24);
    s3.print();
    cout << "-----------------------------" << endl;
    Triangle s4(34, 45, 89, 45, 54, 67);
    s4.print();
    cout << "-----------------------------" << endl;
    Triangle s5(22, 34, 67, 43, 86, 64);
    s5.print();
    return 0;
}

