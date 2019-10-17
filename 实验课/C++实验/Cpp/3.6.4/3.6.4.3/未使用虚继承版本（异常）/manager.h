#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "Employee.h"

class manager: public Employee {
public:
    manager(int number, const std::string& name, bool sex, const Date& birthDate, int job = MANAGER);

    int getSalary() const;
    void Show() const;
};

#endif  // manager.h