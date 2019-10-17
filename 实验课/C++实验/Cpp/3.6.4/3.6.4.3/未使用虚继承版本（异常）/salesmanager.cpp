#include <iostream>
#include "salesmanager.h"

salesmanager::salesmanager(int number,
                           const std::string& name,
                           bool sex,
                           const Date& birthDate,
                           const std::string& dept,
                           int job)
                           : salesman(number, name, sex, birthDate, 0, this, job),
                             manager(number, name, sex, birthDate, job),
                             m_deptName(dept), m_totalSales(0) {}

int salesmanager::getNumber() const {
    return manager::m_number;
}
void salesmanager::setNumber(int number) {
    manager::m_number = number;
    salesman::m_number = number;
}
const std::string& salesmanager::getName() const {
    return manager::m_name;
}
void salesmanager::setName(const std::string& name) {
    manager::m_name = name;
    salesman::m_name = name;
}
bool salesmanager::getSex() const {
    return manager::m_sex;
}
void salesmanager::setSex(bool sex) {
    manager::m_sex = sex;
    salesman::m_sex = sex;
}
const Date& salesmanager::getBirthDate() const {
    return manager::m_birthDate;
}
void salesmanager::setBirthDate(const Date& birthDate) {
    manager::m_birthDate = birthDate;
    salesman::m_birthDate = birthDate;
}
int salesmanager::getJob() const {
    return manager::m_job;
}
void salesmanager::setJob(int job) {
    manager::m_job = job;
    salesman::m_job = job;
}

const std::string& salesmanager::getDeptName() const {
    return m_deptName;
}
void salesmanager::setDeptName(const std::string& dept) {
    m_deptName = dept;
}
int salesmanager::getTotalSales() const {
    return m_totalSales;
}
void salesmanager::alterSales(int value) {
    m_totalSales += value;
}
int salesmanager::getSalary() const {
    return 5000 + static_cast<int>(m_totalSales * 0.005);
}
void salesmanager::Show() const {
    std::cout << "编号: " << manager::m_number << std::endl
              << "姓名: " << manager::m_name << std::endl
              << "性别: " << (manager::m_sex ? "男" : "女") << std::endl
              << "出生日期: " << manager::m_birthDate << std::endl
              << "职位: " << getJobName(manager::m_job) << std::endl
              << "部门名称: " << m_deptName << std::endl
              << "薪水: " << getSalary() << std::endl;
}