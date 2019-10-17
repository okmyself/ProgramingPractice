#include "Date.h"

Date::Date() {
    m_year = 0;
    m_month = 0;
    m_day = 0;
}
Date::Date(int year, int month, int day)
        : m_year(year), m_month(month), m_day(day) {}
int Date::getYear() const {
    return m_year;
}
void Date::setYear(int year) {
    Date::m_year = year;
}
int Date::getMonth() const {
    return m_month;
}
void Date::setMonth(int month) {
    Date::m_month = month;
}
int Date::getDay() const {
    return m_day;
}
void Date::setDay(int day) {
    Date::m_day = day;
}

std::ostream& operator<< (std::ostream& os, const Date& date) {
    os << date.m_year << "年" << date.m_month << "月" << date.m_day << "日";
    return os;
}
