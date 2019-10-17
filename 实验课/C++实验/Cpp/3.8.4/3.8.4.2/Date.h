#ifndef _DATE_H
#define _DATE_H

#include <ostream>

class Date {
private:
    int m_year;
    int m_month;
    int m_day;
public:
    Date();
    Date(int year, int month, int day);
    int getYear() const;
    void setYear(int);
    int getMonth() const;
    void setMonth(int);
    int getDay() const;
    void setDay(int);

    friend std::ostream& operator<< (std::ostream& os, const Date& date);
};

#endif /* Date.h */
