#include <iostream>
#include "SalesCompany.h"
using namespace std;

int main()
{
    cout << "基本员工" << endl;
    Employee emp1;
    emp1.input();
    emp1.print();
    cout << "---------------------------------" << endl;
    cout << "销售员" << endl;
    Salesman emp2;
    emp2.input();
    emp2.print();
    cout << "---------------------------------" << endl;
    cout << "销售经理" << endl;
    Salesmanager emp3;
    emp3.input();
    emp3.print();
    return 0;
}
