#include <iostream>
#include <cmath>
using namespace std;

int main(void) {
    int opt;
    cout << "选择你要进行的运算：" << endl
         << '\t' << "1. 加法" << endl
         << '\t' << "2. 减法" << endl
         << '\t' << "3. 乘法" << endl
         << '\t' << "4. 除法" << endl
         << '\t' << "5. 乘方" << endl
         << '\t' << "6. 开方" << endl
         << '\t' << "7. 正弦" << endl
         << '\t' << "8. 余弦" << endl
         << '\t' << "9. 正切" << endl
         << '\t' << "其他. 退出" << endl;
    cin >> opt;
    while(opt > 0 && opt < 10) {
        float op1, op2;
        switch(opt) {
            case 1:
                cout << "请输入被加数和加数：";
                cin >> op1 >> op2;
                cout << op1 << '+' << op2 << '=' << op1 + op2 << endl;
                break;
            case 2:
                cout << "请输入被减数和减数：";
                cin >> op1 >> op2;
                cout << op1 << '-' << op2 << '=' << op1 - op2 << endl;
                break;
            case 3:
                cout << "请输入被乘数和乘数：";
                cin >> op1 >> op2;
                cout << op1 << '*' << op2 << '=' << op1 * op2 << endl;
                break;
            case 4:
                cout << "请输入被除数和除数：";
                cin >> op1 >> op2;
                cout << op1 << '/' << op2 << '=' << op1 / op2 << endl;
                break;
            case 5:
                cout << "请输入底数和指数：";
                cin >> op1 >> op2;
                cout << op1 << '^' << op2 << '=' << pow(op1, op2) << endl;
                break;
            case 6:
                cout << "请输入被开方数和开方的次数：";
                cin >> op1 >> op2;
                cout << op1 << "^(1/" << op2 << ")=" << pow(op1, 1.0/op2) << endl;
                break;
            case 7:
                cout << "请输入被取正弦的数：";
                cin >> op1;
                cout << "sin(" << op1 << ")=" << sin(op1) << endl;
                break;
            case 8:
                cout << "请输入被取余弦的数：";
                cin >> op1;
                cout << "cos(" << op1 << ")=" << cos(op1) << endl;
                break;
            case 9:
                cout << "请输入被取正切的数：";
                cin >> op1;
                cout << "tan(" << op1 << ")=" << tan(op1) << endl;
                break;
            default:
                break;
        }
        cout << "选择你要进行的运算：" << endl
         << '\t' << "1. 加法" << endl
         << '\t' << "2. 减法" << endl
         << '\t' << "3. 乘法" << endl
         << '\t' << "4. 除法" << endl
         << '\t' << "5. 乘方" << endl
         << '\t' << "6. 开方" << endl
         << '\t' << "7. 正弦" << endl
         << '\t' << "8. 余弦" << endl
         << '\t' << "9. 正切" << endl
         << '\t' << "其他. 退出" << endl;
        cin >> opt;
    }
    return 0;
}
