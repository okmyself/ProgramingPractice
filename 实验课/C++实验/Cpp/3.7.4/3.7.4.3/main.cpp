#include <iostream>
#include "student.h"

using namespace std;


int main()
{
    student stu[2];
    int deg1, deg2, deg3;
    char name[20];
    for (int i = 0; i < sizeof(stu) / sizeof(student); ++i)
    {
        cout << "第" << i + 1 << "个同学: " << endl;
        cout << "姓名: ";
        cin >> name;
        stu[i].setName(name);
        cout << "高数成绩: ";
        cin >> deg1;
        stu[i].setDeg1(deg1);
        cout << "英语成绩: ";
        cin >> deg2;
        stu[i].setDeg2(deg2);
        cout << "计算机成绩: ";
        cin >> deg3;
        stu[i].setDeg3(deg3);

    }
    for (int i = 0; i < sizeof(stu) / sizeof(student); ++i)
        stu[i].display();
    avg(stu, sizeof(stu) / sizeof(student));
    return 0;
}

