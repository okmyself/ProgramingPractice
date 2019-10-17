#include <iostream>
#include "Teacher_Cadre.h"
using namespace std;

int main() {
    int n;
    cout << "请输入数据的个数: n = ";
    cin >> n;
    Teacher_Cadre tc[n];
    for (int i = 0; i < n; i++) {
        char name[20], address[200], phoneNumber[20], title[20], post[20];
        int age, sex, wages;
        cout << "--------------------------------" << endl;
        cout << "请输入第" << i + 1 << "个人的数据: " << endl;
        cout << "姓名: ";
        cin.ignore();
        cin.getline(name, sizeof(name));
        cout << "年龄: ";
        cin >> age;
        cout << "性别(0为女，其他为男): ";
        cin >> sex;
        cout << "地址: ";
        cin.ignore();
        cin.getline(address, sizeof(address));
        cout << "电话: ";
        cin.getline(phoneNumber, sizeof(phoneNumber));
        cout << "职称: ";
        cin.getline(title, sizeof(title));
        cout << "职务: ";
        cin.getline(post, sizeof(post));
        cout << "工资: ";
        cin >> wages;
        tc[i] = Teacher_Cadre(name, age, sex, address, phoneNumber, title, post, wages);
    }
    for (int i = 0; i < n; i++) {
        cout << "--------------------------------" << endl
             << "第" << i + 1 << "个人: " << endl;
        tc[i].Show();
    }
    return 0;
}
