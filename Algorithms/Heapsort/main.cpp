#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <assert.h>
#include "generalfunctions.h"

void heapify(std::vector<int> &arr, int arrSize, int i)
{
    int j, currentVal = arr[0];
    bool wasShifted;
    for (i = arrSize / 2 - 1; i >= 0; --i)
    {
        wasShifted = true;
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

double getTimeOfSort(std::vector<int> &arr,const std::vector<int> &arrCopy, int arrSize, int i)
{
        auto start = std::chrono::high_resolution_clock::now();
        heapSort(arr);
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
    std::ifstream fileIn("arrays.txt", std::ios_base::in);
    std::vector<int> arr;
    arr.reserve(1000000);
    double averageTime = 0;
    while (readArray(arr, fileIn))
    {
        int i;
        for (i = 0; i < 1; ++i)
        {
            std::vector<int> arrCopy(arr);
            int arrSize = arr.size();
            averageTime += getTimeOfSort(arr, arrCopy, arrSize, i);
        }
        std::cout << "Среднее время сортировки: " << averageTime / i <<"s\n";

    }
    fileIn.close();
    return 0;
}
