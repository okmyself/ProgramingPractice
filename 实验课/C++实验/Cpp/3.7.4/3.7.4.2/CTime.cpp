#include "CTime.h"

CTime::CTime(void)
{
    this->m_hour = 0;
    this->m_minute = 0;
    this->m_second = 0;
}
CTime::CTime(int hour, int minute, int second)
{
    this->m_hour = hour;
    this->m_minute = minute;
    this->m_second = second;
}

void CTime::display() const
{
    std::cout << this->m_hour << ':'
              << this->m_minute << ':'
              << this->m_second << std::endl;
}
CTime& CTime::operator++ ()
{
    this->m_second++;
    if (this->m_second == 60)
    {
        this->m_minute++;
        if (this->m_minute == 60)
        {
            this->m_hour++;
            if (this->m_hour == 24)
            {
                this->m_hour = 0;
            }
            this->m_minute = 0;
        }
        this->m_second = 0;
    }
    return *this;
}
CTime CTime::operator++ (int)
{
    CTime temp(*this);

    temp.m_hour = this->m_hour;
    temp.m_minute = this->m_minute;
    temp.m_second = this->m_second;
    this->m_second++;
    if (this->m_second == 60)
    {
        this->m_minute++;
        if (this->m_minute == 60)
        {
            this->m_hour++;
            if (this->m_hour == 24)
            {
                this->m_hour = 0;
            }
            this->m_minute = 0;
        }
        this->m_second = 0;
    }
    return temp;
}
int CTime::getHour() const
{
    return this->m_hour;
}
void CTime::setHour(int hour)
{
    if (hour >= 0 && hour <= 24)
        this->m_hour = hour;
    else
        this->m_hour = 0;
}
int CTime::getMinute() const
{
    return this->m_minute;
}
void CTime::setMinute(int minute)
{
    if (minute >= 0 && minute <= 60)
        this->m_minute = minute;
    else
        this->m_minute = 0;
}
int CTime::getSecond() const
{
    return 0;
}
void CTime::setSecond(int second)
{
    if (second >= 0 && second <= 60)
        this->m_second = second;
    else
        this->m_second = 0;
}

