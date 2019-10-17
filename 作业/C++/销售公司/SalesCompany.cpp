#include "SalesCompany.h"
#include <iostream>
#include <cstring>
// 一般员工
Employee::Employee(const char number[], const char name[], float basicSalary) {
    strcpy(this->number, number);
    strcpy(this->name, name);
    this->basicSalary = basicSalary;
}
void Employee::input()
{
    std::cout << "姓名：";
    std::cin >> name;
    std::cout << "编号：";
    std::cin >> number;
}
void Employee::print() {
    std::cout << "一般员工：" << name << std::endl
              << "编号：" << number << std::endl
              << "工资：" << basicSalary << std::endl;
}
// 销售员工
float Salesman::commrate = 0.005;
Salesman::Salesman(int sales) {
    this->sales = sales;
}
void Salesman::input() {
    Employee::input();
    std::cout << "销售额：";
    std::cin >> sales;
}
void Salesman::pay() {
    salary = basicSalary + sales * commrate;
}
void Salesman::print() {
    pay();
    std::cout << "销售员工：" << name << std::endl
              << "编号：" << number << std::endl
              << "工资：" << salary << std::endl;
}
// 销售经理
Salesmanager::Salesmanager(float jobSalary) {
    this->jobSalary = jobSalary;
}
void Salesmanager::input() {
    Employee::input();
    std::cout << "销售额：";
    std::cin >> sales;
}
void Salesmanager::pay() {
    salary = jobSalary + sales * commrate;
}
void Salesmanager::print() {
    pay();
    std::cout << "销售经理 ：" << name << std::endl
              << "编号：" << number << std::endl
              << "工资：" << salary << std::endl;
}