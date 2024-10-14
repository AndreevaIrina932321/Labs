#include <iostream>
#include "Array.h"

int main()
{
    Array arr0(6, 2), arr1(3, 3);
    arr0.print();
    for (int i = arr0.getSize() - 1; i >= 0; --i)
        arr0[arr0.getSize() - 1 - i]= i;
    arr0.print();
    arr0.erase(arr0.begin(), arr0.end(), 2);
    arr0.print();
    return 0;
}
