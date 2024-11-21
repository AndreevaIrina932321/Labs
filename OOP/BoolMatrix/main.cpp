#include <iostream>
#include "BoolMatrix.h"

int main()
{
    //BoolMatrix a(17, 2, true);
    char **arr = new char *[2];
    for (int i = 0; i < 2; ++i)
    {
        arr[i] = new char[3];
    }
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cin >> arr[i][j];
        }
    }
    BoolMatrix a(arr, 2, 3);
    a.print();
    for (int i = 0; i < 2; ++i)
    {
        delete [] arr[i];
    }
    delete arr;
    return 0;
}
