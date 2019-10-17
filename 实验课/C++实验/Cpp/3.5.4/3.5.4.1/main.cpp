#include <iostream>
#include "Figure.h"
using namespace std;

int main(void)
{
    Circle(30, 45, 35).Show();
    cout << "----------------------------------" << endl;
    Circle(50, 89, 23).Show();
    cout << "----------------------------------" << endl;
    Rectangle(28, 24).Show();
    cout << "----------------------------------" << endl;
    Triangle(10, 12).Show();
    cout << "----------------------------------" << endl;
    Triangle(-1, 12).Show();
    cout << "----------------------------------" << endl;
    return 0;
}
