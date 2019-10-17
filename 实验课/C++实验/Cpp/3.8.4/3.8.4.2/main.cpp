#include <iostream>
#include "Employee.h"
#include "manager.h"
#include "salesmanager.h"
#include "salesman.h"
#include "technician.h"
#define NAME_LEN 100
using namespace std;

int main()
{
    int n;
    char deptName[NAME_LEN];
    cout << "请输入员工人数: ";
    cin >> n;
    Employee* e[n];
    for (int i = 0; i < n; i++) {
        int number, job;
        string name;
        int sex, year, month, day;
        cout << "请输入第" << i + 1 << "个员工信息: " << endl;
        while(true) {
            int j;
            cout << "编号: ";
            cin >> number;
            for (j = 0; j < i; j++) {
                if (e[j]->getNumber() == number)
                    break;
            }
            if (j == i) break;
            cout << "编号已存在, 请重新输入!" << endl;
        }
        cout << "姓名: ";
        cin >> name;
        cout << "性别(0表示女，其他数字代表男): ";
        cin >> sex;
        cout << "出生日期(以年月日用空格分开的形式输入): ";
        cin >> year >> month >> day;
        cout << "职位("
             << MANAGER << '-' << getJobName(MANAGER) << ',' << ' '
             << SALESMANAGER << '-' << getJobName(SALESMANAGER) << ',' << ' '
             << SALESMAN << '-' << getJobName(SALESMAN) << ',' << ' '
             << TECHNICIAN << '-' << getJobName(TECHNICIAN) << ')' << ':' << ' ';
        cin >> job;
        while (job != MANAGER && job != SALESMANAGER && job != SALESMAN && job != TECHNICIAN)
        {
            cout << "输入有误，请重新输入: " << endl;
            cout << "职位("
                 << MANAGER << '-' << getJobName(MANAGER) << ',' << ' '
                 << SALESMANAGER << '-' << getJobName(SALESMANAGER) << ',' << ' '
                 << SALESMAN << '-' << getJobName(SALESMAN) << ',' << ' '
                 << TECHNICIAN << '-' << getJobName(TECHNICIAN) << ')' << ':' << ' ';
            cin >> job;
        }
        int workHour, sales, dept, j;
        switch (job)
        {
            case MANAGER:   // 编号、姓名、性别、出生日期、职位
                e[i] = new manager(number, name, sex, Date(year, month, day));
                break;
            case SALESMANAGER:  // 编号、姓名、性别、出生日期、职位、所属部门
                cout << "所属部门名称: ";
                cin >> deptName;
                e[i] = new salesmanager(number, name, sex, Date(year, month, day), deptName);
                break;
            case SALESMAN:  // 编号、姓名、性别、出生日期、职位、所属部门
                cout << "销售额: ";
                cin >> sales;
                cout << "所属部门部门经理的编号: ";
                cin >> dept;
                for (j = 0; j < i; j++) {
                    if (e[j]->getNumber() == dept) {
                        dept = j;
                        break;
                    }
                }
                if (j == i) {
                    cout << "该部门尚未录入或不存在，请保证在录入销售员工之前录入销售经理! " << endl;
                    exit(0);
                }
                e[i] = new salesman(number, name, sex, Date(year, month, day), sales, dynamic_cast<salesmanager*> (e[dept]));
                break;
            case TECHNICIAN:    // 编号、姓名、性别、出生日期、职位、工作时间
                cout << "工作时间: ";
                cin >> workHour;
                e[i] = new technician(number, name, sex, Date(year, month, day), workHour);
                break;
            default:
                break;
        }
    }
    cout << "信息录入完毕!" << endl;

    int s;
    cout << "功能: " << endl
         << "1. 显示所有员工编号和姓名" << endl
         << "2. 查询员工信息(按编号)" << endl
         << "3. 查询员工信息(按姓名)" << endl
         << "4. 修改员工信息" << endl
         << "5. 升职" << endl
         << "其他. 退出" << endl;
    cin >> s;
    while(s == 1 || s == 2 || s == 3 || s == 4 || s == 5) {
        string name;
        int i, number, dept;
        switch(s) {
            case 1:
                for (i = 0; i < n; i++) {
                    cout << e[i]->getNumber() << '-' << e[i]->getName() << endl;
                }
                break;
            case 2:
                cout << "请输入员工编号: ";
                cin >> number;
                i = inquire(e, n, number);
                if (i == -1)
                    cout << "未找到该员工!" << endl;
                else
                    e[i]->display();
                break;
            case 3:
                cout << "请输入员工姓名: ";
                cin >> name;
                i = inquire(e, n, name);
                if (i == -1)
                    cout << "未找到该员工!" << endl;
                else
                    e[i]->display();
                break;
            case 4:
                cout << "请输入员工编号: ";
                cin >> number;
                cout << "请输入修改后的信息: ";
                for (i = 0; i < n; i++) {
                    if (e[i]->getNumber() == number) {
                        int job, sales;
                        int sex, year, month, day, workHour;
                        job = e[i]->getJob();
                        switch (job) {
                            case SALESMANAGER:
                                cout << "姓名: ";
                                cin >> name;
                                e[i]->setName(name);
                                cout << "性别(0表示女，其他数字代表男): ";
                                cin >> sex;
                                e[i]->setSex(sex);
                                cout << "出生日期(以年月日用空格分开的形式输入): ";
                                cin >> year >> month >> day;
                                e[i]->setBirthDate(Date(year, month, day));
                                break;
                            case SALESMAN:
                                cout << "姓名: ";
                                cin >> name;
                                e[i]->setName(name);
                                cout << "性别(0表示女，其他数字代表男): ";
                                cin >> sex;
                                e[i]->setSex(sex);
                                cout << "出生日期(以年月日用空格分开的形式输入): ";
                                cin >> year >> month >> day;
                                e[i]->setBirthDate(Date(year, month, day));
                                cout << "销售额: ";
                                cin >> sales;
                                dynamic_cast<salesman*>(e[i])->setSales(sales);
                                cout << "所属部门部门经理的编号: ";
                                cin >> dept;
                                int j;
                                for (j = 0; j < i; j++) {
                                    if (e[j]->getNumber() == dept) {
                                        dept = j;
                                        break;
                                    }
                                }
                                if (j == i) {
                                    cout << "该部门尚未录入或不存在，请保证在录入销售员工之前录入销售经理! " << endl;
                                    exit(0);
                                }
                                dynamic_cast<salesman*>(e[i])->setDept(dynamic_cast<salesmanager*> (e[dept]));
                                break;
                            case TECHNICIAN:
                                cout << "姓名: ";
                                cin >> name;
                                e[i]->setName(name);
                                cout << "性别(0表示女，其他数字代表男): ";
                                cin >> sex;
                                e[i]->setSex(sex);
                                cout << "出生日期(以年月日用空格分开的形式输入): ";
                                cin >> year >> month >> day;
                                e[i]->setBirthDate(Date(year, month, day));
                                cout << "工作时间: ";
                                cin >> workHour;
                                dynamic_cast<technician*>(e[i])->setWorkHour(workHour);
                                break;
                            default:
                                break;
                        }
                        cout << "修改成功!" << endl;
                        break;
                    }
                }
                if (i == n)
                    cout << "未找到该员工!" << endl;
                break;
            case 5:
                cout << "请输入员工编号: ";
                cin >> number;
                i = inquire(e, n, number);
                if (i == -1)
                    cout << "未找到该员工!" << endl;
                else
                    e[i]->promote();
                break;
        }
        cout << "功能: " << endl
             << "1. 显示所有员工编号和姓名" << endl
             << "2. 查询员工信息(按编号)" << endl
             << "3. 查询员工信息(按姓名)" << endl
             << "4. 修改员工信息" << endl
             << "5. 升职" << endl
             << "其他. 退出" << endl;
        cin >> s;
    }
    return 0;
}
