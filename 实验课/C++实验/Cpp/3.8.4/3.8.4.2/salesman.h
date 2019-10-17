#ifndef _SALESMAN_H_
#define _SALESMAN_H_

#include <string>
#include "Employee.h"

class salesmanager; // 前向声明
class salesman: virtual public Employee {
protected:
    int m_sales;  // 销售额
    salesmanager* m_dept;   // 所属部门(以部门经理代替)
public:
    salesman(int number,
             const std::string& name,
             bool sex,
             const Date& birthDate,
             int sales,
             salesmanager* dept,
             int job = SALESMAN);
    virtual ~salesman();
    salesmanager* getDept() const;
    void setDept(salesmanager* dept);
    int getSales() const;
    void setSales(int sales);
    virtual int pay() const;
    virtual void display() const;
    virtual void promote();
};

#endif // salesman.h
