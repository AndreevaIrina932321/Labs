#include <iostream>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "List.h"

template <typename T>
void printSearchResult(const List<T>& list, const T& value)
{
    std::cout << "list ";
    auto it = std::find(list.begin(), list.end(), value);
    if (it == list.end())
    {
        std::cout << "doesn't contain ";
    }
    else
    {
        std::cout << "contains ";
    }
    std::cout << "'" << value << "' value.\n";
}


int main()
{
    List<std::string> list;
    list.append("aboba");
    list.append("bobao");
    list.append("pshh-pshh");
    list.print();
    std::vector<std::string> arr;
    arr.resize(3, "aboba");
    List<std::string> list1(list);
    list1.append("gogo");
    list1.append("momo");
    list1.print();
    std::cout << list1.min();
    /*std::cout << "Введите элементы списка: ";
    list1.input();*/
    auto it = list1.searchElement("bobao");
    auto it1 = list1.searchElement("gogo");
    list.erase(it);
    list1.print();
    list1 += list;
    list1.sort();
    list1.print();
    return 0;
}
