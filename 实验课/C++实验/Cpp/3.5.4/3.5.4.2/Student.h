#include <string>
#include <iostream>

class Student {
private:
    static int m_studentID;
    std::string m_name;
    bool m_sex;
    struct {
        int year;
        int month;
    } m_date;
    std::string m_grade;  //年级
    std::string m_class;  //班级
    std::string m_faculty;    //院系
    std::string m_major;  //专业
public:
    Student();
    Student(const Student& s);
    Student(std::string,
            bool = true,
            int = 85,
            int = 11,
            std::string = std::string("05级"),
            std::string = std::string("jy01"),
            std::string = std::string("computer"),
            std::string = std::string("application"));
    void SetInfo(std::string,
                 bool = true,
                 int = 85,
                 int = 11,
                 std::string = std::string("05级"),
                 std::string = std::string("jy01"),
                 std::string = std::string("computer"),
                 std::string = std::string("application"));
    void Show();
};
