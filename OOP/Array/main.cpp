#include <iostream>
#include "Array.h"

int main()
{
    Array<int> arr0(4, 5);
    std::cin >> arr0;
    std::cout << arr0;
    /*for (int i = arr0.getSize() - 1; i >= 0; --i)
        arr0[arr0.getSize() - 1 - i]= i;*/
    std::cout << arr0;
    arr0.erase(arr0.begin(), arr0.end(), 2);
    std::cout << arr0;
    return 0;
}
