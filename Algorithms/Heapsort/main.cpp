#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <assert.h>
#include "generalfunctions.h"

void heapify(std::vector<int> &arr, int arrSize, int i)
{
    int j, currentVal = arr[i];
    bool wasShifted = true;
    j = i * 2 + 1;
    currentVal  = arr[i];
    while (j < arrSize && wasShifted)
    {
        if (j + 1 < arrSize && arr[j + 1] > arr[j])
        {
            ++j;
        }
        if (arr[j] > currentVal)
        {
            arr[i] = arr[j];
            i = j;
            j = i * 2 + 1;
        }
        else
        {
            wasShifted = false;
        }
    }
    arr[i] = currentVal;
}

void heapSort(std::vector<int> &arr)
{
    int arrSize = arr.size(), i;
    for (i = arrSize / 2 - 1; i >= 0; --i)
    {
        heapify(arr, arrSize, i);
    }
    for (int i = arrSize - 1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

double getTimeOfSort(std::vector<int> arr, int arrSize)
{
        auto start = std::chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        assert(isSorted(arr));
        std::chrono::duration<double> diff = end - start;
        return diff.count();
}


int main()
{
    std::ifstream fileIn("/home/rin/ForLabs/algorithms/ShellSort/arrays.txt", std::ios_base::in);
    std::vector<int> arr;
    arr.reserve(1000000);
    int range = 10, outCounter = 1;
    while (readArray(arr, fileIn))
    {
        int i;
        double averageTime = 0;
        for (i = 0; i < 3; ++i)
        {
            int arrSize = arr.size();
            averageTime += getTimeOfSort(arr, arrSize);
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
