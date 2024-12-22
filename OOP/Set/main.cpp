#include <iostream>
#include "Set.h"


int main()
{
    char *a = new char [5] {'a', 'b', 'c', 'd', 'e'};
    Set set(a, 5), set1(set), set2(set);
    std::cout << set;
    std::cout << set1;
    set2 = set1 & set;
    set = set - 'b';
    std::cout << set;
    return 0;
}
