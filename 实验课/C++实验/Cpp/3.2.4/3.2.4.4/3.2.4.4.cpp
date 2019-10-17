#include<iostream>
//假设两个矩阵分别是A*B和B*C矩阵
#define A 4
#define B 3
#define C 2
using namespace std;

void MatrixMul(int a[A][B], int b[B][C], int c[A][C]) {
    int i, j, k;
    for (i = 0; i < A; i++) {
        for (j = 0; j < C; j++) {
            c[i][j] = 0;
            for (k = 0; k < B; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(void) {
    int i, j, k;
    int a[A][B], b[B][C], c[A][C];
    cout << "请输入矩阵A: " << endl;
    for (i = 0; i < A; i++)
        for (j = 0; j < B; j++)
            cin >> a[i][j];
    cout << "请输入矩阵B: " << endl;
    for (i = 0; i < B; i++)
        for (j = 0; j < C; j++)
            cin >> b[i][j];
    MatrixMul(a, b, c);
    for (i = 0; i < A; i++) {
        for (j = 0; j < C; j++)
            cout << c[i][j] << '\t';
        cout << '\n';
    }
    return 0;
}
