#include <iostream>
using namespace std;
void averscore(int sco[][5], int avsco[5]) {
    for(int i = 0; i < 5; i++) {
        avsco[i] = 0;
        for(int j = 0; j < 5; j++) {
            avsco[i] += sco[i][j];
        }
        avsco[i] /= 5;
    }
}
int avercourse(int (*psco)[5], int n) {
    int result = 0;
    for(int i = 0; i < 5; i++) {
        result += psco[i][n - 1];
    }
    return result / 5;
}
int main(void)
{
    int num[5];
    int sco[5][5];
    int avsco[5];
    cout << "请输入5名学生的信息：" << endl
         << "学号" << '\t'
         << "课程1" << '\t'
         << "课程2" << '\t'
         << "课程3" << '\t'
         << "课程4" << '\t'
         << "课程5" << endl;
    for(int i = 0; i < 5; i++) {
        cin >> num[i]
            >> sco[i][0]
            >> sco[i][1]
            >> sco[i][2]
            >> sco[i][3]
            >> sco[i][4];
    }
    cout << "----------------------------------------------------------" << endl;
    averscore(sco, avsco);
    cout << "学号" << '\t'
         << "课程1" << '\t'
         << "课程2" << '\t'
         << "课程3" << '\t'
         << "课程4" << '\t'
         << "课程5" << '\t'
         << "平均成绩" << endl;
    for(int i = 0; i < 5; i++) {
        cout << num[i] << '\t'
             << sco[i][0] << '\t'
             << sco[i][1] << '\t'
             << sco[i][2] << '\t'
             << sco[i][3] << '\t'
             << sco[i][4] << '\t'
             << avsco[i] << endl;
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "课程的平均成绩：" << endl;
    for(int i = 0; i < 5; i++) {
        cout << '\t' << "课程" << i + 1 << "："
             << avercourse(sco, i + 1) << endl;
    }
    return 0;
}
