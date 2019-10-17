#include <iostream>
#include "Employee.h"
using namespace std;

int main()
{
//    Employee e[4] = {
//            Employee(10001, "jack", true, Date(80, 11, 1)),
//            Employee(10002, "andy", true, Date(75, 1, 9)),
//            Employee(10003, "alex", true, Date(81, 4, 3)),
//            Employee(10004, "lili", false, Date(82, 10, 1))
//    };
    int n;
    cout << "请输入员工人数: ";
    cin >> n;
    Employee e[n];
    for (int i = 0; i < n; i++) {
        int number;
        string name, job;
        int sex, year, month, day;
        cout << "请输入第" << i + 1 << "个员工信息: " << endl;
        do {
            int j;
            cout << "编号: ";
            cin >> number;
            for (j = 0; j < i; j++) {
                if (e[j].getNumber() == number)
                    break;
            }
            if (j == i) break;
            cout << "编号已存在, 请重新输入!" << endl;
        } while(true);
        cout << "姓名: ";
        cin >> name;
        cout << "性别(0表示女，其他数字代表男): ";
        cin >> sex;
        cout << "出生日期(以年月日用空格分开的形式输入): ";
        cin >> year >> month >> day;
        cout << "职位: ";
        cin >> job;
        e[i] = Employee(number, name, sex, Date(year, month, day), job);
    }
    cout << "信息录入完毕!" << endl;

    int s;
    cout << "功能: " << endl
         << "1. 显示所有员工编号和姓名" << endl
         << "2. 查询员工信息(按编号)" << endl
         << "3. 查询员工信息(按姓名)" << endl
         << "4. 修改员工信息" << endl
         << "其他. 退出" << endl;
    cin >> s;
    while(s == 1 || s == 2 || s == 3 || s == 4) {
        string name;
        int i, number;
        switch(s) {
            case 1:
                for (i = 0; i < n; i++) {
                    cout << e[i].getNumber() << '-' << e[i].getName() << endl;
                }
                break;
            case 2:
                cout << "请输入员工编号: ";
                cin >> number;
                i = inquire(e, n, number);
                if (i == -1)
                    cout << "未找到该员工!" << endl;
                else
                    e[i].Show();
                break;
            case 3:
                cout << "请输入员工姓名: ";
                cin >> name;
                i = inquire(e, n, name);
                if (i == -1)
                    cout << "未找到该员工!" << endl;
                else
                    e[i].Show();
                break;
            case 4:
                cout << "请输入员工编号: ";
                cin >> number;
                cout << "请输入修改后的信息: ";
                for (i = 0; i < n; i++) {
                    if (e[i].getNumber() == number) {
                        string name, job;
                        int sex, year, month, day;
                        cout << "姓名: ";
                        cin >> name;
                        e[i].setName(name);
                        cout << "性别(0表示女，其他数字代表男): ";
                        cin >> sex;
                        e[i].setSex(sex);
                        cout << "出生日期(以年月日用空格分开的形式输入): ";
                        cin >> year >> month >> day;
                        e[i].setBirthDate(Date(year, month, day));
                        cout << "职位: ";
                        cin >> job;
                        e[i].setJob(job);
                        cout << "修改成功!" << endl;
                        break;
                    }
                }
                if (i == n)
                    cout << "未找到该员工!" << endl;
                break;
            default:
                break;
        }
        cout << "功能: " << endl
             << "1. 显示所有员工编号和姓名" << endl
             << "2. 查询员工信息(按编号)" << endl
             << "3. 查询员工信息(按姓名)" << endl
             << "4. 修改员工信息" << endl
             << "其他. 退出" << endl;
        cin >> s;
    }
    return 0;
}
