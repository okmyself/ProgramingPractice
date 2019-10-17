#include <iostream>
#include "Shape.h"
using namespace std;

int main()
{
    Sphere a(1);
    Column b(1,2);
    cout << a.area() << endl;
    cout << a.volume() << endl;
    cout << b.area() << endl;
    cout << b.volume() << endl;
}
