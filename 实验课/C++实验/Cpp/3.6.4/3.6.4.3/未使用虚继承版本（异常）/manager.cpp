#include <iostream>
#include "manager.h"

manager::manager(int number,
                 const std::string &name,
                 bool sex,
                 const Date &birthDate,
                 int job)
        : Employee(number, name, sex, birthDate, MANAGER) {}
int manager::getSalary() const {
    return 8000;
}
void manager::Show() const {
    std::cout << "编号: " << m_number << std::endl
              << "姓名: " << m_name << std::endl
              << "性别: " << (m_sex ? "男" : "女") << std::endl
              << "出生日期: " << m_birthDate << std::endl
              << "职位: " << getJobName(m_job) << std::endl
              << "薪水: " << getSalary() << std::endl;
}