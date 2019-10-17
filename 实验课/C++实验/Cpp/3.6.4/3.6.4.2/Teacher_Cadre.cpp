#include "Teacher_Cadre.h"

Teacher_Cadre::Teacher_Cadre() {}
Teacher_Cadre::Teacher_Cadre(const std::string& name,
                             int age, bool sex,
                             const std::string& address,
                             const std::string& phoneNumber,
                             const std::string& title,
                             const std::string& post,
                             int wages)
                             : Teacher(name, age, sex, address, phoneNumber, title),
                               Cadre(name, age, sex, address, phoneNumber, post), m_wages(wages) {}
void Teacher_Cadre::Show() {
    Teacher::display();
}
