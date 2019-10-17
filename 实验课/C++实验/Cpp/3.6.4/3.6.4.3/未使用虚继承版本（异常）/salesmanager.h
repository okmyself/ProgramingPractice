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

    int getNumber() const;
    void setNumber(int number);
    const std::string& getName() const;
    void setName(const std::string& name);
    bool getSex() const;
    void setSex(bool sex);
    const Date& getBirthDate() const;
    void setBirthDate(const Date& birthDate);
    int getJob() const;
    void setJob(int job);

    const std::string& getDeptName() const;
    void setDeptName(const std::string& dept);
    int getTotalSales() const;
    void alterSales(int value); // 正值增加，负值减少
    int getSalary() const;
    void Show() const;
};

#endif // salesmanager.h