#include<iostream>

using namespace std;
struct Student {
    int num;
    char name[32];
    float fScore;
};

void swap(Student *a, Student *b)
{
    Student t = *a;
    *a = *b;
    *b = t;
}

int main(void)
{
    Student stu[100];
    // ... 初始化100个学生信息
    int len = sizeof(stu) / sizeof(Student);
    for(int i = 0; i < len - 1; i++)
    {
        int max = i;
        for(int j = i + 1; j < len; j++)
        {
            if(stu[max].fScore < stu[j].fScore)
                max = j;
        }
        if(max != i)
            swap(&stu[max], &stu[i]);
    }
    // 排序完毕
    return 0;
}