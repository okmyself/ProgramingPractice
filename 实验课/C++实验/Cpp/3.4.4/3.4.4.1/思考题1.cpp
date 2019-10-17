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
    int *p = (int*) &day1;
    cout << "please enter year month day: ";
    cin >> *p >> *(p + 1) >> *(p + 2);
    if(*p < 1 || *(p + 1) < 1 || *(p + 1) > 12 || *(p + 2) < 1)  //年月日不合法
        cout << "input error!" << endl;
    else
    {
        int total = 0;
        monthDays[1] = ( *p%4==0 && *p%100!=0 ) || (*p%400==0) ? 29 : 28; //计算这一年二月的天数
        if(*(p + 2) > monthDays[*(p + 1) - 1])  //日期不合法
            cout << "input error!" << endl;
        else
        {
            for(int i = 0; i < *(p + 1) - 1; i++)
                total += monthDays[i];      //计算这一年1月1日到这一月1日经过的天数
            total += *(p + 2);   //加上这个月的天数
            cout << *p << "年" << *(p + 1) << "月" << *(p + 2) << "日是这一年中第" << total << "天" << endl;
        }
    }
    return 0;
}
