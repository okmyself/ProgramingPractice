#include <iostream>
#include "String.h"

using namespace std;

int main() {
    char str1[100], str2[100];
    cin >> str1;
    cin >> str2;
    String a(str1), b(str2);
    if (a > b)
        cout << a << " > " << b << endl;
    else if (a == b)
        cout << a << " == " << b << endl;
    else
        cout << a << " < " << b << endl;
    return 0;
}
