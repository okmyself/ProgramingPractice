#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "Employee.h"

class manager: virtual public Employee {
public:
    manager(int number, const std::string& name, bool sex, const Date& birthDate, int job = MANAGER);

    virtual int pay() const;
    virtual void display() const;
    virtual void promote();
};

#endif  // manager.h