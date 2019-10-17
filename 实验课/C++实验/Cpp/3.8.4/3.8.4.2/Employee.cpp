#include <iostream>
#include "Employee.h"

Employee::Employee(): m_number(0), m_sex(true) {}
Employee::Employee(int number,
                   const std::string& name,
                   bool sex,
                   const Date& birthDate,
                   int job)
        : m_number(number), m_name(name),
          m_sex(sex), m_birthDate(birthDate),
          m_job(job) {}
Employee::~Employee() {}

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
int Employee::getJob() const {
    return m_job;
}
void Employee::setJob(int job) {
    m_job = job;
}

int inquire(Employee* e[], int len, int number) {
    for (int i = 0; i < len; i++) {
        if (e[i]->m_number == number)
            return i;
    }
    return -1;  //找不到返回-1
}
int inquire(Employee* e[], int len, const std::string& name) {
    for (int i = 0; i < len; i++) {
        if (e[i]->m_name == name)
            return i;
    }
    return -1;
}

void Employee::promote() {}

const char* getJobName(int job) {
    switch (job) {
        case MANAGER:
            return "总经理";
        case SALESMANAGER:
            return "销售经理";
        case SALESMAN:
            return "销售员";
        case TECHNICIAN:
            return "技术人员";
        default: ;
    }
    return "undefined";
}