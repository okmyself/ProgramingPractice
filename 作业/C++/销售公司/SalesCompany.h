#ifndef _SALES_COMPANY_H_
#define _SALES_COMPANY_H_

class Employee {
protected:
    char number[20];
    char name[20];
    float basicSalary;
public:
    Employee(const char[] = "\0", const char[] = "\0", float = 2000);
    void input();
    void print();
};

class Salesman: public Employee {
protected:
    static float commrate; //提成比例
    int sales;  // 销售额
    float salary;
public:
    Salesman(int = 0);
    void input();
    void pay();
    void print();
};
class Salesmanager: public Salesman {
private:
    float jobSalary;
public:
    Salesmanager(float = 3000);
    void input();
    void pay();
    void print();
};

#endif /* SalesCompay.h */