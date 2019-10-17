#include <iostream>
#include "LinkList.h"
using namespace std;

int main(void)
{
    LinkList L;
    L.Insert(1, 'H');
    L.Insert(2, 'e');
    L.Insert(3, 'l');
    L.Insert(4, 'l');
    L.Insert(5, 'o');
    L.Delete('r');
    L.Display();
    return 0;
}
