#include <iostream>
#include "salesman.h"
#include "Employee.h"
#include "salesmanager.h"

salesman::salesman(int number,
                   const std::string& name,
                   bool sex,
                   const Date& birthDate,
                   int sales,
                   salesmanager* dept,
                   int job)
                   : Employee(number, name, sex, birthDate, job)
                   , m_sales(sales), m_dept(dept) {
    m_dept->alterSales(sales);
}
salesman::~salesman() {
    m_dept->alterSales(-m_sales);
}
int salesman::getSales() const {
    return m_sales;
}
void salesman::setSales(int sales) {
    m_dept->alterSales(sales - m_sales);
    m_sales = sales;
}
salesmanager* salesman::getDept() const {
    return m_dept;
}
void salesman::setDept(salesmanager* dept) {
    m_dept->alterSales(-m_sales);
    m_dept = dept;
    m_dept->alterSales(m_sales);
}
int salesman::pay() const {
    return static_cast<int>(0.04 * m_sales);
}
void salesman::display() const {
    std::cout << "编号: " << m_number << std::endl
              << "姓名: " << m_name << std::endl
              << "性别: " << (m_sex ? "男" : "女") << std::endl
              << "出生日期: " << m_birthDate << std::endl
              << "职位: " << getJobName(m_job) << std::endl
              << "所属部门: " << m_dept->getDeptName() << std::endl
              << "销售额: " << m_sales << std::endl
              << "薪水: " << pay() << std::endl;
}
void salesman::promote() {
    std::cout << "恭喜" << m_name << "升职为" << getJobName(SALESMANAGER) << std::endl;
}
