#include <iostream>
using namespace std;

void SelectSort(int arr[], int len)
{
    for(int i = 0; i < len; i++) {
        int maximum = i;
        for(int j = i + 1; j < len; j++)
            if(arr[j] > arr[maximum])
                maximum = j;
        if(maximum != i) {
            //swap
            int temp = arr[i];
            arr[i] = arr[maximum];
            arr[maximum] = temp;
        }
    }
}
int BinarySearch(int elem, int arr[], int len) {
    int l = 0, h = len - 1, m;
    while(l <= h) {
        m = (l + h) >> 1;
        if(arr[m] > elem)
            l = m + 1;
        else if(arr[m] < elem)
            h = m - 1;
        else
            return m;
    }
    return -1;
}
int main(void)
{
    int score[15];
    cout << "请输入15个学生的成绩: " << endl;
    for(int i = 0; i < 15; i++) {
        cin >> score[i];
        if(score[i] < 0 || score[i] > 100) {
            cout << "输入错误" << endl;
            return -1;
        }
    }
    SelectSort(score, sizeof(score) / sizeof(int));
    int elem;
    cout << "请输入一个成绩: ";
    cin >> elem;
    int ranking = BinarySearch(elem, score, sizeof(score) / sizeof(int)) + 1;
    if(ranking == 0)
        cout << "无此成绩";
    else
        cout << ranking;
    return 0;
}
