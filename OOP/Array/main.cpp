#include <iostream>
#include "Array.h"

int main()
{
    Array a(10, 1), b(a);
    a.print();
    a.insertElement(2, 4);
    a.print();
    a.deleteAll(1);
    a.print();
    a += b;
    a.print();
    return 0;
}
