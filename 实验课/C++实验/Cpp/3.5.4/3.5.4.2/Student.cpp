#include "Student.h"

int Student::m_studentID = 0;
Student::Student() { m_studentID++; }
Student::Student(const Student& s) {
    m_studentID++;
    m_name = s.m_name;
    m_sex = s.m_sex;
    m_date.year = s.m_date.year;
    m_date.month = s.m_date.month;
    m_grade = s.m_grade;
    m_class = s.m_class;
    m_faculty = s.m_faculty;
    m_major = s.m_major;
}   //拷贝构造函数
Student::Student(std::string name,
                 bool sex,
                 int year,
                 int month,
                 std::string grade,
                 std::string class_,
                 std::string faculty,
                 std::string major) {
    if(year < 0 || year > 2019 || month < 1 || month > 12)
        throw "年级输入错误";
    m_studentID++;
    m_sex = sex;
    m_name = name;
    m_date.year = year;
    m_date.month = month;
    m_grade = grade;
    m_class = class_;
    m_faculty = faculty;
    m_major = major;
}
void Student::SetInfo(std::string name,
                      bool sex,
                      int year,
                      int month,
                      std::string grade,
                      std::string class_,
                      std::string faculty,
                      std::string major) {
    if(year < 0 || year > 2019 || month < 1 || month > 12)
        throw "年级输入错误";
    m_name = name;
    m_sex = sex;
    m_date.year = year;
    m_date.month = month;
    m_grade = grade;
    m_class = class_;
    m_faculty = faculty;
    m_major = major;
}
void Student::Show() {
    std::cout << "学号：" << m_studentID << std::endl
              << "姓名：" << m_name << std::endl
              << "性别：" << (m_sex ? "男" : "女") << std::endl
              << "出生日期：" << m_date.year << "年" << m_date.month << "月" << std::endl
              << "年级：" << m_grade << std::endl
              << "班级：" << m_class << std::endl
              << "院系：" << m_faculty << std::endl
              << "专业：" << m_major << std::endl;
}
