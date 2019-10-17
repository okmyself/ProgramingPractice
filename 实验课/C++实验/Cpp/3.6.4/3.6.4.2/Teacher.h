#ifndef _TEACHER_H_
#define _TEACHER_H_

#include <string>

class Teacher {
private:
    std::string m_name;
    int m_age;
    bool m_sex;   // false表示女，true表示男
    std::string m_address;
    std::string m_phoneNumber;
    std::string m_title;
public:
    Teacher();
    Teacher(const std::string& name,
            int age, bool sex,
            const std::string& address,
            const std::string& phoneNumber,
            const std::string& title);
    const std::string& getName() const;
    void setName(const std::string& name);
    int getAge() const;
    void setAge(int age);
    bool getSex() const;
    void setSex(bool sex);
    const std::string& getAddress() const;
    void setAddress(const std::string& address);
    const std::string& getPhoneNumber() const;
    void setPhoneNumber(const std::string& phoneNumber);
    const std::string& getTitle() const;
    void setTitle(const std::string& title);
    void display();
};

#endif // Teacher.h
