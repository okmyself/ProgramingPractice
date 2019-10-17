#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <string>
#include "Date.h"

class Employee {
private:
    int m_number;
    std::string m_name;
    bool m_sex;   // true-男, false-女
    Date m_birthDate;
    std::string m_job;
public:
    Employee();
    Employee(int number, const std::string &name, bool sex = true, const Date &birthDate = Date(),
             const std::string &job = std::string("普通"));

    int getNumber() const;
    void setNumber(int number);
    const std::string& getName() const;
    void setName(const std::string &name);
    bool getSex() const;
    void setSex(bool sex);
    const Date& getBirthDate() const;
    void setBirthDate(const Date& birthDate);
    const std::string& getJob() const;
    void setJob(const std::string& job);

    void Show();

    friend int inquire(Employee e[], int len, int number);
    friend int inquire(Employee e[], int len, const std::string& name);
};

#endif /* Employee.h */
