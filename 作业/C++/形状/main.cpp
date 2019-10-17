#include <iostream>
#include "Shape.h"
using namespace std;

int main()
{
    Shape s0;
    s0.print();
    cout << "-----------------------------" << endl;
    TwoDimShape s1;
    s1.print();
    cout << "-----------------------------" << endl;
    ThreeDimShape s2(100, 80, "ThreeDimShape");
    s2.print();
    cout << "-----------------------------" << endl;
    Rectangle s3(3, 4);
    s3.print();
    cout << "-----------------------------" << endl;
    Triangle s4(3, 4, 5);
    s4.print();
    cout << "-----------------------------" << endl;
    Circle s5(2);
    s5.print();
    cout << "-----------------------------" << endl;
    Cuboid s6(7, 8, 9);
    s6.print();
    cout << "-----------------------------" << endl;
    Sphere s7(3);
    s7.print();
    return 0;
}
