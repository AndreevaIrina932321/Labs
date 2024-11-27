#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <assert.h>
#include "generalfunctions.h"

void qSort(std::vector<int> &arr, int leftIndex, int rightIndex)
{
    if (leftIndex >= rightIndex)
    {
        return;
    }
    int i = leftIndex, j = rightIndex, pivot = arr[(i + j) / 2];
    while (i <= j)
    {
        while (arr[i] < pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }

    qSort(arr, leftIndex, j);
    qSort(arr, i, rightIndex);
}


double getTimeOfSort(std::vector<int> &arr,const std::vector<int> &arrCopy, int arrSize, int i)
{
    auto start = std::chrono::high_resolution_clock::now();
    qSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    assert(isSorted(arr));
    if (i != 2)
    {
        arr = arrCopy;
    }
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

int main()
{
    std::ifstream fileIn("/home/rin/ForLabs/algorithms/ShellSort/arrays.txt", std::ios_base::in);
    std::vector<int> arr;
    arr.reserve(1000000);
    double averageTime = 0;
    int range = 10, outCounter = 1;
    while (readArray(arr, fileIn))
    {
        int i;
        for (i = 0; i < 3; ++i)
        {
            std::vector<int> arrCopy(arr);
            int arrSize = arr.size();
            averageTime += getTimeOfSort(arr, arrCopy, arrSize, i);
        }
        std::cout << "Размер массива: [" << arr.size() << ']' << " Диапазон значений: -"
                  << range << '/' << range << std::endl;
        std::cout << "Среднее время сортировки: " << averageTime / i <<"s\n";
        if (outCounter % 3 == 0)
        {
            range *= 100;
        }
        ++outCounter;
    }
    fileIn.close();
    return 0;
}
