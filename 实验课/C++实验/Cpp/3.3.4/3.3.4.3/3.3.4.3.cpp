#include <iostream>
using namespace std;

void SelectSort(int *arr, int len)
{
    for(int i = 0; i < len; i++) {
        int maximum = i;
        for(int j = i + 1; j < len; j++)
            if(*(arr + j) > *(arr + maximum))
                maximum = j;
        if(maximum != i) {
            //swap
            int temp = *(arr + i);
            *(arr + i) = *(arr + maximum);
            *(arr + maximum) = temp;
        }
    }
}
int BinarySearch(int elem, int *arr, int len) {
    int l = 0, h = len - 1, m;
    while(l <= h) {
        m = (l + h) >> 1;
        if(*(arr + m) > elem)
            l = m + 1;
        else if(*(arr + m) < elem)
            h = m - 1;
        else
            return m;
    }
    return -1;
}
int main(void)
{
    int intArr[15];
    cout << "请输入15个整数: " << endl;
    for(int i = 0; i < 15; i++) {
        cin >> intArr[i];
    }
    SelectSort(intArr, sizeof(intArr) / sizeof(int));
    int elem;
    cout << "请输入一个数: ";
    cin >> elem;
    int ranking = BinarySearch(elem, intArr, sizeof(intArr) / sizeof(int)) + 1;
    if(ranking == 0)
        cout << "无此数";
    else
        cout << ranking;
    return 0;
}
