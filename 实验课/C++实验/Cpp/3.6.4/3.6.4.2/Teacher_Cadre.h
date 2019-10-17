#ifndef _TEACHER_CADRE_H_
#define _TEACHER_CADRE_H_

#include "Teacher.h"
#include "Cadre.h"

class Teacher_Cadre: Teacher, Cadre {
private:
    int m_wages;
public:
    Teacher_Cadre();
    Teacher_Cadre(const std::string& name,
                  int age, bool sex,
                  const std::string& address,
                  const std::string& phoneNumber,
                  const std::string& title,
                  const std::string& post,
                  int wages);
    void Show();
};

#endif // Teacher.h
