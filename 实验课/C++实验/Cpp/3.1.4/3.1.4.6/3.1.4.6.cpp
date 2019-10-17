//#include<iostream>
//using namespace std;
//static int monthDays[] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   //12个月每个月的天数
//static char* weekDays[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
//inline int getDayOfYear(int year)   //获得某一年的天数
//{
//    return ( year%4==0 && year%100!=0 ) || (year%400==0) ? 366 : 365;
//}
//int main()
//{
//    int year, month, day;
//    cout << "please enter year month day: ";
//    cin >> year >> month >> day;
//    while(year != 0 && month != 0 && day != 0)  //任意一个输入为0则停止继续执行
//    {
//        if(year < 1 || month < 1 || month > 12 || day < 1)  //年月日不合法
//            cout << "input error!" << endl;
//        else
//        {
//            int dayOfWeek = 1, total = 0;
//            monthDays[1] = getDayOfYear(year) == 365 ? 28 : 29; //计算这一年二月的天数
//            if(day > monthDays[month - 1])  //日期不合法
//                cout << "input error!" << endl;
//            else
//            {
//                for(int i = 1; i < year; i++)
//                    total += getDayOfYear(i);   //计算1年1月1日到这一年1月1日经过的天数
//                for(int i = 0; i < month - 1; i++)
//                    total += monthDays[i];      //计算这一年1月1日到这一月1日经过的天数
//                total += day;   //加上这个月的天数
//                cout << year << "年" << month << "月" << day << "日是" << weekDays[total % 7] << endl;
//            }
//        }
//        cout << "please enter year month day: ";
//        cin >> year >> month >> day;
//    }
//    return 0;
//}
