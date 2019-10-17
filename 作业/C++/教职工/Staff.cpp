#include "Staff.h"

Staff::Staff(float basicSalary) {
    Staff::basicSalary = basicSalary;
}
float Staff::getBasicSalary() const {
    return basicSalary;
}
void Staff::setBasicSalary(float basicSalary) {
    Staff::basicSalary = basicSalary;
}

Teacher::Teacher(float basicSalary, enum title title, int classHour) : Staff(basicSalary) {
    Teacher::title = title;
    Teacher::classHour = classHour;
}
enum title Teacher::getTitle() const {
    return title;
}
void Teacher::setTitle(enum title title) {
    Teacher::title = title;
}
int Teacher::getClassHour() const {
    return classHour;
}
void Teacher::setClassHour(int classHour) {
    Teacher::classHour = classHour;
}
float Teacher::salary() const {
    return basicSalary + title * classHour;
}

Manager::Manager(float basicSalary, float postSalary): Staff(basicSalary) {
    Manager::postSalary = postSalary;
}
float Manager::getPostSalary() const {
    return postSalary;
}
void Manager::setPostSalary(float postSalary) {
    Manager::postSalary = postSalary;
}
float Manager::salary() const {
    return basicSalary + postSalary;
}

Lab::Lab(float basicSalary, float dailySubsidy, int workDayPerMonth): Staff(basicSalary) {
    Lab::dailySubsidy = dailySubsidy;
    Lab::workDayPerMonth = workDayPerMonth;
}
float Lab::getDailySubsidy() const {
    return dailySubsidy;
}
void Lab::setDailySubsidy(float dailySubsidy) {
    Lab::dailySubsidy = dailySubsidy;
}
int Lab::getWorkDayPerMonth() const {
    return workDayPerMonth;
}
void Lab::setWorkDayPerMonth(int workDayPerMonth) {
    Lab::workDayPerMonth = workDayPerMonth;
}
float Lab::salary() const {
    return basicSalary + dailySubsidy * workDayPerMonth;
}