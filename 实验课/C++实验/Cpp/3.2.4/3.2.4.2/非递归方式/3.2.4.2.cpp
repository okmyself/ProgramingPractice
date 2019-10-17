#include<iostream>
using namespace std;
double fn(int n)   //计算n!
{
    double result = 1;
    for(int i = n; i > 1; i--)
        result *= i;
    return result;
}

inline int Cnr(int n, int r)   //计算组合数C(n,r)
{
    return static_cast<int>(fn(n) / (fn(n - r) * fn(r)));
}

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
