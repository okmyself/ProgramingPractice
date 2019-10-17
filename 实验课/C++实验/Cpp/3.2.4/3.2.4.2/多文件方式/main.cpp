#include <iostream>
#include "func.h"
using namespace std;

int main(void)
{
    int n, r;
    cout << "n=";
    cin >> n;
    cout << "r=";
    cin >> r;
    while(n != 0 || r != 0)
    {
        if(n >= 1 && n >= r)
        {
            cout << "C(" << n << "," << r << ")=" << Cnr(n, r) << endl;
        }
        else
            cout << "input error!" << endl;
        cout << "n=";
        cin >> n;
        cout << "r=";
        cin >> r;
    }
    return 0;
}

