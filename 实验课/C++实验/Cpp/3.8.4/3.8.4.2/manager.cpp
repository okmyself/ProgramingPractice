#include <iostream>
#include "manager.h"

manager::manager(int number,
                 const std::string &name,
                 bool sex,
                 const Date &birthDate,
                 int job)
        : Employee(number, name, sex, birthDate, MANAGER) {}
int manager::pay() const {
    return 8000;
}
void manager::display() const {
    std::cout << "编号: " << m_number << std::endl
              << "姓名: " << m_name << std::endl
              << "性别: " << (m_sex ? "男" : "女") << std::endl
              << "出生日期: " << m_birthDate << std::endl
              << "职位: " << getJobName(m_job) << std::endl
              << "薪水: " << pay() << std::endl;
}

void manager::promote() {
    std::cout << "您已经是" << getJobName(m_job) << "了，不能再升职了!" << std::endl;
}
