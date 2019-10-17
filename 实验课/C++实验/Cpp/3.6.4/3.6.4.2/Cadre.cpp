#include <iostream>
#include "Cadre.h"

Cadre::Cadre() {}
Cadre::Cadre(const std::string& name,
             int age, bool sex,
             const std::string& address,
             const std::string& phoneNumber,
             const std::string& post)
             : m_name(name), m_age(age), m_sex(sex),
               m_address(address), m_phoneNumber(phoneNumber),
               m_post(post) {}
const std::string& Cadre::getName() const {
    return m_name;
}
void Cadre::setName(const std::string& name) {
    m_name = name;
}
int Cadre::getAge() const {
    return m_age;
}
void Cadre::setAge(int age) {
    m_age = age;
}
bool Cadre::getSex() const {
    return m_sex;
}
void Cadre::setSex(bool sex) {
    m_sex = sex;
}
const std::string& Cadre::getAddress() const {
    return m_address;
}
void Cadre::setAddress(const std::string& address) {
    m_address = address;
}
const std::string& Cadre::getPhoneNumber() const {
    return m_phoneNumber;
}
void Cadre::setPhoneNumber(const std::string& phoneNumber) {
    m_phoneNumber = phoneNumber;
}
const std::string& Cadre::getPost() const {
    return m_post;
}
void Cadre::setPost(const std::string& post) {
    m_post = post;
}
void Cadre::display() {
    std::cout << "姓名: " << m_name << std::endl
              << "年龄: " << m_age << std::endl
              << "性别: " << (m_sex ? "男" : "女") << std::endl
              << "地址: " << m_address << std::endl
              << "手机号: " << m_phoneNumber << std::endl
              << "职务: " << m_post << std::endl;
}
