#include "CTime.h"

int main()
{
    CTime t1(13, 45, 45);
    (t1++).display();
    (++t1).display();
    CTime t2(23, 58, 5);
    (++t2).display();
    (t2++).display();
    return 0;
}
