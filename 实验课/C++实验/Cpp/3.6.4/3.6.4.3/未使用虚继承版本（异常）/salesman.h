#ifndef _SALESMAN_H_
#define _SALESMAN_H_

#include <string>
#include "Employee.h"

class salesmanager; // 前向声明
class salesman: public Employee {
protected:
    int m_sales;  // 销售额
    salesmanager* m_dept;   // 所属部门
public:
    salesman(int number,
             const std::string& name,
             bool sex,
             const Date& birthDate,
             int sales,
             salesmanager* dept,
             int job = SALESMAN);
    ~salesman();
    salesmanager* getDept() const;
    void setDept(salesmanager* dept);
    int getSales() const;
    void setSales(int sales);
    int getSalary() const;
    void Show() const;
};

#endif // salesman.h
