#ifndef _CTIME_H_
#define _CTIME_H_

#include <iostream>

class CTime
{
private:
    int m_hour;
    int m_minute;
    int m_second;
public:
    CTime(void);
    CTime(int hour, int minute, int second);
    CTime(const CTime& t)
    {
        this->m_hour = t.m_hour;
        this->m_minute = t.m_minute;
        this->m_second = t.m_second;
    }
    void display() const;
    CTime& operator++();
    CTime operator++(int);
    int getHour() const;
    void setHour(int hour);
    int getMinute() const;
    void setMinute(int minute);
    int getSecond() const;
    void setSecond(int second);
};

#endif // CTime.h

