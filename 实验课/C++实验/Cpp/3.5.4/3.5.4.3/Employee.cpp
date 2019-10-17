#include <iostream>
#include "Employee.h"

Employee::Employee(): m_number(0), m_sex(true) {}
Employee::Employee(int number,
                   const std::string& name,
                   bool sex,
                   const Date& birthDate,
                   const std::string& job)
                   : m_number(number), m_name(name),
                   m_sex(sex), m_birthDate(birthDate),
                   m_job(job) {}

int Employee::getNumber() const {
    return m_number;
}
void Employee::setNumber(int number) {
    m_number = number;
}
const std::string& Employee::getName() const {
    return m_name;
}
void Employee::setName(const std::string& name) {
    m_name = name;
}
bool Employee::getSex() const {
    return m_sex;
}
void Employee::setSex(bool sex) {
    m_sex = sex;
}
const Date& Employee::getBirthDate() const {
    return m_birthDate;
}
void Employee::setBirthDate(const Date& birthDate) {
    m_birthDate = birthDate;
}
const std::string& Employee::getJob() const {
    return m_job;
}
void Employee::setJob(const std::string& job) {
    m_job = job;
}

int inquire(Employee e[], int len, int number) {
    for (int i = 0; i < len; i++) {
        if (e[i].m_number == number)
            return i;
    }
    return -1;  //找不到返回-1
}
int inquire(Employee e[], int len, const std::string& name) {
    for (int i = 0; i < len; i++) {
        if (e[i].m_name == name)
            return i;
    }
    return -1;
}

void Employee::Show() {
    std::cout << "编号: " << m_number << std::endl
              << "姓名: " << m_name << std::endl
              << "性别: " << (m_sex ? "男" : "女") << std::endl
              << "出生日期: " << m_birthDate << std::endl;
}
