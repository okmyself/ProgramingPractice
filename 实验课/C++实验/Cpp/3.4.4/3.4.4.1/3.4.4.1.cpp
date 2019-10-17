#include <iostream>
using namespace std;
static int monthDays[] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   //12个月每个月的天数
struct date {
    int year;
    int month;
    int day;
};
int main(void) {
    date day1;
    cout << "please enter year month day: ";
    cin >> day1.year >> day1.month >> day1.day;
    if(day1.year < 1 || day1.month < 1 || day1.month > 12 || day1.day < 1)  //年月日不合法
        cout << "input error!" << endl;
    else
    {
        int total = 0;
        monthDays[1] = ( day1.year%4==0 && day1.year%100!=0 ) || (day1.year%400==0) ? 29 : 28; //计算这一年二月的天数
        if(day1.day > monthDays[day1.month - 1])  //日期不合法
            cout << "input error!" << endl;
        else
        {
            for(int i = 0; i < day1.month - 1; i++)
                total += monthDays[i];      //计算这一年1月1日到这一月1日经过的天数
            total += day1.day;   //加上这个月的天数
            cout << day1.year << "年" << day1.month << "月" << day1.day << "日是这一年中第" << total << "天" << endl;
        }
    }
    return 0;
}
