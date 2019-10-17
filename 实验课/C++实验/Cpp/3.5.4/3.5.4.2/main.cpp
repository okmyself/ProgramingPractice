#include <iostream>
#include "Student.h"
using namespace std;

int main()
{
    string name;
    int sex;
    int year;
    int month;
    string grade;
    string class_;
    string faculty;
    string major;
    Student stu1("张三");
    stu1.Show();
    cout << "-----------------------------" << endl;
    Student stu2;
    cout << "请输入姓名：";
    cin >> name;
    cout << "请输入性别（1代表男，其他代表女）：";
    cin >> sex;
    cout << "请输入出生年份：";
    cin >> year;
    cout << "请输入出生月份：";
    cin >> month;
    cout << "请输入年级：";
    cin >> grade;
    cout << "请输入班级：";
    cin >> class_;
    cout << "请输入院系：";
    cin >> faculty;
    cout << "请输入专业：";
    cin >> major;
    stu2.SetInfo(name, sex == 1, year, month, grade, class_, faculty, major);
    cout << "-----------------------------" << endl;
    stu2.Show();
    return 0;
}
