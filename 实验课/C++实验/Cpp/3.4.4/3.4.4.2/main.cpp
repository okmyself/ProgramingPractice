#include <iostream>
#include "Student.h"
using namespace std;

int main()
{
    Student stu[20]; //定义有20 个变量的元素的结构体数组（根据需要//确定数组的大小）。
    int stu_number = 0 ; //学生个数
    cout<< "please enter student number:";
    cin >> stu_number ; //输入学生个数
    for( int i = 0; i < stu_number; i++)
    {
        cout << "please enter NO. " << i << " student info : num name class score1 score2 score3" << endl;
        cin >> stu[i].num >> stu[i].name >> stu[i].classname;
        cin >> stu[i].score[0] >> stu[i].score[1] >> stu[i].score[2];
    }
    averagescore(stu, stu_number);
    for( int i = 0; i < stu_number; i++)
        cout << "学生" << stu[i].name << "的平均分为" << stu[i].aver_score << endl;
    cout << "平均分最高的学生为" << stu[max_averagescore(stu, stu_number)].name;
    return 0;
}
