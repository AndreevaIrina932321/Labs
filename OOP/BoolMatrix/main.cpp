#include <iostream>
#include "BoolMatrix.h"

int main()
{
    BoolMatrix m1(4, 3, true), m2(5, 4, true);
    BoolMatrix m3(m1);
    m1.input();
    m2.input();
    m3 = m1 ^ m2;
    m3.print();
    return 0;
}
