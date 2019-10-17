#include <iostream>
using namespace std;
void averscore(int stu_info[5][7]) {
    for(int i = 0; i < 5; i++) {
        stu_info[i][6] = 0;
        for(int j = 1; j < 6; j++) {
            stu_info[i][6] += stu_info[i][j];
        }
        stu_info[i][6] /= 5;
    }
}
int avercourse(int (*psco)[7], int n) {
    int result = 0;
    for(int i = 0; i < 5; i++) {
        result += psco[i][n];
    }
    return result / 5;
}
int main(void)
{
    int stu_info[5][7];
    cout << "请输入5名学生的信息：" << endl
         << "学号" << '\t'
         << "课程1" << '\t'
         << "课程2" << '\t'
         << "课程3" << '\t'
         << "课程4" << '\t'
         << "课程5" << endl;
    for(int i = 0; i < 5; i++) {
        cin >> stu_info[i][0]   //学号
            >> stu_info[i][1]   //课程1成绩
            >> stu_info[i][2]   //课程2成绩
            >> stu_info[i][3]   //课程3成绩
            >> stu_info[i][4]   //课程4成绩
            >> stu_info[i][5];  //课程5成绩
        stu_info[i][6] = 0;     //平均成绩
    }
    cout << "----------------------------------------------------------" << endl;
    averscore(stu_info);
    cout << "学号" << '\t'
         << "课程1" << '\t'
         << "课程2" << '\t'
         << "课程3" << '\t'
         << "课程4" << '\t'
         << "课程5" << '\t'
         << "平均成绩" << endl;
    for(int i = 0; i < 5; i++) {
        cout << stu_info[i][0] << '\t'
             << stu_info[i][1] << '\t'
             << stu_info[i][2] << '\t'
             << stu_info[i][3] << '\t'
             << stu_info[i][4] << '\t'
             << stu_info[i][5] << '\t'
             << stu_info[i][6] << endl;
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "课程的平均成绩：" << endl;
    for(int i = 0; i < 5; i++) {
        cout << '\t' << "课程" << i + 1 << "："
             << avercourse(stu_info, i + 1) << endl;
    }
    return 0;
}
