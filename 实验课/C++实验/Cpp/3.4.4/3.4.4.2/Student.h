struct Student
{
    int num; //学号
    char name[20]; //班级注意字节长度
    char classname[20]; //班级
    float score[3]; //三门课程成绩
    float aver_score; //平均分
};
void averagescore(Student stu[], int number);
int max_averagescore(Student stu[], int number);
