#include <iostream>
#include "Shape.h"
using namespace std;

int main()
{
    Shape* shape;
    Circle s0(30, 45, 35);
    shape = &s0;
    shape->print();
    cout << "-----------------------------" << endl;
    Circle s1(50, 89, 23);
    shape = &s1;
    shape->print();
    cout << "-----------------------------" << endl;
    Rectangle s2(30, 53);
    shape = &s2;
    shape->print();
    cout << "-----------------------------" << endl;
    Rectangle s3(28, 24);
    shape = &s3;
    shape->print();
    cout << "-----------------------------" << endl;
    Triangle s4(34, 45, 89, 45, 54, 67);
    shape = &s4;
    shape->print();
    cout << "-----------------------------" << endl;
    Triangle s5(22, 34, 67, 43, 86, 64);
    shape = &s5;
    shape->print();
    return 0;
}
