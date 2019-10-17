#include <iostream>
#include "Staff.h"
using namespace std;
int main()
{
    Teacher t(5500, LECTURER, 7);
    cout << "教师的工资: " << t.salary() << endl;
    Manager m(5000, 1000);
    cout << "管理人员的工资: " << m.salary() << endl;
    Lab l(4000, 60, 20);
    cout << "实验室人员的工资: " << l.salary() << endl;
    return 0;
}