#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include <cstring>

using namespace std;

class student
{
private:
    char m_name[20];
    int m_deg1, m_deg2, m_deg3;
public:
    void setName(const char* name);
    const char *getName() const;
    int getDeg1() const;
    void setDeg1(int deg1);
    int getDeg2() const;
    void setDeg2(int deg2);
    int getDeg3() const;
    void setDeg3(int deg3);

    student();
    student(char na[], int d1, int d2, int d3);
    student(student& s);
    void display();
    friend student operator+(const student& s1, const student& s2);
    friend void avg(student s[], int n);
};

#endif /* student.h */
