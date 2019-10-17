//#include<iostream>
//using namespace std;
//void func1()
//{
//    double worktime, wageph, wage;
//    cout << "Please input employee’s work time and wage_per_hour:";
//    cin >> worktime >> wageph;
//    if(worktime <= 40)      //周工作不超过40小时
//        wage = wageph * worktime;
//    else if(worktime <= 60) //周工作超过40小时且不超过60小时
//        wage = 40 * wageph + (worktime - 40) * wageph * 1.5;
//    else                //周工作时间超过60小时
//        wage = 40 * wageph + 20 * wageph * 1.5 + (worktime - 60) * wageph * 3;
//    cout << "The employee’s wage :" << wage;
//}
//
//void func2()
//{
//    int count;
//    double worktime, wageph, wage;
//    cout << "Please input employee’s work time and wage_per_hour:";
//    cin >> worktime >> wageph;
//    if(worktime > 60) count = 3;
//    else count = worktime / 20;
//    switch(count)
//    {
//        case 0:
//        case 1:
//        {
//            wage = worktime * wageph;
//            break;
//        }
//        case 2:
//        {
//            wage = ((worktime - 40) * 1.5 + 40) * wageph;
//            break;
//        }
//        case 3:
//        {
//            wage = (((worktime - 60) * 3.0 + (60 - 40) * 1.5) + 40) * wageph;
//            break;
//        }
//    }
//    cout << "The employee’s wage :" << wage;
//}
//int main(void)
//{
////    func1();
//    func2();
//    return 0;
//}
