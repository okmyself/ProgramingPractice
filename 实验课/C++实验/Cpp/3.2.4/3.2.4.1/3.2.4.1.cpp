//#include<iostream>
//using namespace std;
//int n = 0;
//int func(int x = 10);
//int main()
//{
//
//    int a, b;
//    a = 5;
//    b = func(a);
//    cout << "\nlocal a=" << a << endl
//            << "local b=" << b << endl
//            << "global n=" << n << endl;
//    a++;
//    b = func(a);
//    cout << "\nlocal a=" << a <<endl
//         << "local b=" << b << endl
//         << "global n=" << n << endl;
//    func();
//    return 0;
//}
//
//int func(int x)
//{
//    int a = 1;
//    static int b = 10;
//    a++;
//    b++;
//    x++;
//    n++;
//    cout << "\nlocal a=" << a << endl
//         << "local b=" << b << endl
//         << "parameter x=" << x << endl;
//    return a+b;
//}
