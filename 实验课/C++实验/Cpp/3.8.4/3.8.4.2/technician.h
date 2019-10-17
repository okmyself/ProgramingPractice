#ifndef _TECHNICIAN_H_
#define _TECHNICIAN_H_

#include "Employee.h"

class technician: public Employee {
protected:
    int m_workHour;
public:
    technician(int number,
               const std::string& name,
               bool sex,
               const Date& birthDate,
               int workHour);
    int getWorkHour() const;
    void setWorkHour(int workHour);
    int pay() const;
    void display() const;
    virtual void promote();
};

#endif // technician.h
