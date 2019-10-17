#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#define MANAGER 1
#define SALESMANAGER 2
#define SALESMAN 3
#define TECHNICIAN 4

#include <string>
#include "Date.h"

class Employee {
protected:
    int m_number;
    std::string m_name;
    bool m_sex;   // true-男, false-女
    Date m_birthDate;
    int m_job;
public:
    Employee();
    Employee(int number,
             const std::string &name,
             bool sex = true,
             const Date &birthDate = Date(),
             int job = 0);
    virtual ~Employee();

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

    virtual int getSalary() const;
    virtual void Show() const;

    friend int inquire(Employee* e[], int len, int number);
    friend int inquire(Employee* e[], int len, const std::string& name);
};

const char* getJobName(int job);

#endif /* Employee.h */