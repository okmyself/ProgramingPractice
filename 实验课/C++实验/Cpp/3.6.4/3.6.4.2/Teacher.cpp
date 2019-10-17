#include <iostream>
#include "Teacher.h"

Teacher::Teacher() {}
Teacher::Teacher(const std::string& name,
        int age, bool sex,
        const std::string& address,
        const std::string& phoneNumber,
        const std::string& title)
        : m_name(name), m_age(age), m_sex(sex),
          m_address(address), m_phoneNumber(phoneNumber),
          m_title(title) {}
void Teacher::display() {
    std::cout << "姓名: " << m_name << std::endl
              << "年龄: " << m_age << std::endl
              << "性别: " << (m_sex ? "男" : "女") << std::endl
              << "地址: " << m_address << std::endl
              << "手机号: " << m_phoneNumber << std::endl
              << "职称: " << m_title << std::endl;
}
const std::string& Teacher::getName() const {
    return m_name;
}
void Teacher::setName(const std::string &name) {
    m_name = name;
}
int Teacher::getAge() const {
    return m_age;
}
void Teacher::setAge(int age) {
    m_age = age;
}
bool Teacher::getSex() const {
    return m_sex;
}
void Teacher::setSex(bool sex) {
    m_sex = sex;
}
const std::string& Teacher::getAddress() const {
    return m_address;
}
void Teacher::setAddress(const std::string& address) {
    m_address = address;
}
const std::string& Teacher::getPhoneNumber() const {
    return m_phoneNumber;
}
void Teacher::setPhoneNumber(const std::string& phoneNumber) {
    m_phoneNumber = phoneNumber;
}
const std::string& Teacher::getTitle() const {
    return m_title;
}
void Teacher::setTitle(const std::string& title) {
    m_title = title;
}
