#include "student.h"

student::student() {
    for (int i = 0; i < 10; ++i) {
        this->m_name[i] = '\0';
    }
    this->m_deg1 = 0;
    this->m_deg2 = 0;
    this->m_deg3 = 0;
}
student::student(char *na, int d1, int d2, int d3) {
    this->m_deg1 = d1;
    this->m_deg2 = d2;
    this->m_deg3 = d3;

    strcpy(m_name, na);
}
student::student(student &s) {
    this->m_deg1 = s.m_deg1;
    this->m_deg2 = s.m_deg2;
    this->m_deg3 = s.m_deg3;

    strcpy(m_name, s.m_name);
}
void student::display() {
    cout << "姓名" << '\t'
         << "高数" << '\t'
         << "英语" << '\t'
         << "计算机" << endl;

    cout << m_name << '\t'
         << m_deg1 << '\t'
         << m_deg2 << '\t'
         << m_deg3 << endl;
}
student operator+ (const student& s1, const student& s2) {
    student temp;
    temp.m_deg1 = s1.m_deg1 + s2.m_deg1;
    temp.m_deg2 = s1.m_deg2 + s2.m_deg2;
    temp.m_deg3 = s1.m_deg3 + s2.m_deg3;

    return temp;
}
void avg(student s[], int n) {
    student temp;
    for (int i = 0; i < n; i++) {
        temp = temp + s[i];
    }
    cout << "高数平均分: " << (temp.m_deg1 / n) << endl
         << "英语平均分: " << (temp.m_deg2 / n) << endl
         << "计算机平均分: " << (temp.m_deg3 / n) << endl;
}

void student::setName(const char* name) {
    strcpy(m_name, name);
}
const char *student::getName() const {
    return m_name;
}
int student::getDeg1() const {
    return m_deg1;
}
void student::setDeg1(int deg1) {
    m_deg1 = deg1;
}
int student::getDeg2() const {
    return m_deg2;
}
void student::setDeg2(int deg2) {
    m_deg2 = deg2;
}
int student::getDeg3() const {
    return m_deg3;
}
void student::setDeg3(int deg3) {
    m_deg3 = deg3;
}
