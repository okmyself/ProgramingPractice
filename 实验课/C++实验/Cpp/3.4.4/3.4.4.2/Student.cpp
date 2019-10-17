#include "Student.h"

void averagescore(Student stu[], int number)
{
    for(int i = 0; i < number; i++)
    {
        stu[i].aver_score = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2]) / 3.0;
    }
}

int max_averagescore(Student stu[], int number)
{
    int k = 0;
    //查找最高平均分并记录在数组中的下标值
    for(int i = 0; i < number; i++)
    {
        if(stu[i].aver_score > stu[k].aver_score)
            k = i;
    }
    return k; //返回最高平均分数组元素的下标
}
