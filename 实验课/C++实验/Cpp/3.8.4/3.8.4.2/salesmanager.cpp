#include <iostream>
#include "salesmanager.h"

salesmanager::salesmanager(int number,
                           const std::string& name,
                           bool sex,
                           const Date& birthDate,
                           const std::string& dept,
                           int job)
                           : Employee(number, name, sex, birthDate, job),
                             salesman(number, name, sex, birthDate, 0, this, job),
                             manager(number, name, sex, birthDate, job),
                             m_deptName(dept), m_totalSales(0) {}

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
int salesmanager::pay() const {
    return 5000 + static_cast<int>(m_totalSales * 0.005);
}
void salesmanager::display() const {
    std::cout << "编号: " << manager::m_number << std::endl
              << "姓名: " << manager::m_name << std::endl
              << "性别: " << (manager::m_sex ? "男" : "女") << std::endl
              << "出生日期: " << manager::m_birthDate << std::endl
              << "职位: " << getJobName(manager::m_job) << std::endl
              << "部门名称: " << m_deptName << std::endl
              << "薪水: " << pay() << std::endl;
}

void salesmanager::promote() {
    std::cout << "恭喜" << m_name << "升职为" << getJobName(MANAGER) << std::endl;
}
