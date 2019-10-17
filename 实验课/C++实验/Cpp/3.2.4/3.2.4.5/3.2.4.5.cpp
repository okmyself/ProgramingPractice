#include <iostream>
#include <cstring>
#include <string>
#define LEN1 20
#define LEN2 10
using namespace std;
char* mystrcat(char *dest, char *src) {
    char *p = dest, *q = src;
    while(*p) p++;
    while(*q) {
        *p = *q;
        p++;
        q++;
    }
    *p = '\0';
    return dest;
}
int main(void) {
    char a[LEN1], b[LEN2];
    cout << "请输入两个字符串: " << endl;
    cin.getline(a, LEN1);
    cin.getline(b, LEN2);
    mystrcat(a, b);
    cout << "mystrcat拼接后的字符串为: " << endl;
    cout << a << endl;
    cout << "请输入两个字符串: " << endl;
    cin.getline(a, LEN1);
    cin.getline(b, LEN2);
    strcat(a, b);
    cout << "strcat拼接后的字符串为: " << endl;
    cout << a << endl;
    string c, d;
    cout << "请输入两个字符串: " << endl;
    cin >> c >> d;
    c.append(d);
    cout << "string拼接后的字符串为: " << endl;
    cout << c << endl;
    return 0;
}
