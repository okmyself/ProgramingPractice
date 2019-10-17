#include <iostream>
#include "technician.h"

technician::technician(int number,
    const std::string& name,
    bool sex,
    const Date& birthDate,
    int workHour)
    : Employee(number, name, sex, birthDate, TECHNICIAN)
    , m_workHour(workHour) {}

int technician::getWorkHour() const {
    return m_workHour;
}
void technician::setWorkHour(int workHour) {
    m_workHour = workHour;
}
int technician::pay() const {
    return 25 * m_workHour;
}
void technician::display() const {
    std::cout << "编号: " << m_number << std::endl
              << "姓名: " << m_name << std::endl
              << "性别: " << (m_sex ? "男" : "女") << std::endl
              << "出生日期: " << m_birthDate << std::endl
              << "职位: " << getJobName(m_job) << std::endl
              << "工作时间: " << m_workHour << std::endl
              << "薪水: " << pay() << std::endl;
}

void technician::promote() {
    std::cout << "恭喜" << m_name << "升职为" << getJobName(MANAGER) << std::endl;
}
