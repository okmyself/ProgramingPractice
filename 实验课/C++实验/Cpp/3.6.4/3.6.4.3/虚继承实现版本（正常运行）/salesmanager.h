#ifndef _SALESMANAGER_H_
#define _SALESMANAGER_H_

#include "salesman.h"
#include "manager.h"

class salesmanager: public manager, public salesman {
protected:
    std::string m_deptName; // 部门名称
    int m_totalSales;   // 销售总额，自动计算得到
public:
    salesmanager(int number,
                 const std::string& name,
                 bool sex,
                 const Date& birthDate,
                 const std::string& dept,
                 int job = SALESMANAGER);

    const std::string& getDeptName() const;
    void setDeptName(const std::string& dept);
    int getTotalSales() const;
    void alterSales(int value); // 正值增加，负值减少
    virtual int getSalary() const;
    virtual void Show() const;
};

#endif // salesmanager.h