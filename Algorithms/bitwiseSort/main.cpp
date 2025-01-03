#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include <assert.h>
#include "generalfunctions.h"

bool getBit(const int k, int sample)
{
    int mask = 1;
    mask = mask << k;
    return mask & sample;
}

int getEldestBit(const std::vector<int> &arr)
{
    int i = 30, maxValue = *(std::max_element(arr.begin(), arr.end()));
    while(!getBit(i, maxValue))
    {
        --i;
    }
    return i;
}

void preSort(std::vector<int> &arr, int &pLeftIndex, int &pRightIndex, int &nLeftIndex, int &nRightIndex)
{
    nLeftIndex = 0;
    pRightIndex = arr.size() - 1;
    int i = 0, j = arr.size() - 1;
    while (i <= j)
    {
        while (getBit(31, arr[i]))
        {
            i++;
        }

        while (getBit(31, arr[j]) == false)
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
    nRightIndex = j;
    pLeftIndex = i;
}

void bSort(std::vector<int> &arr, int leftIndex, int rightIndex, int k)
{
    if (leftIndex >= rightIndex || k < 0)
    {
        return;
    }
    int i = leftIndex, j = rightIndex;
    while (i <= j)
    {
        while (i <= j && getBit(k, arr[i]) == false)
        {
            i++;
        }

        while (i <= j && getBit(k, arr[j]))
        {
            j--;
        }

        if (i < j)
        {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }
    bSort(arr, leftIndex, j, k - 1);
    bSort(arr, i, rightIndex, k - 1);
}

void bitwiseSort(std::vector<int> &arr, int eldestBit)
{
    int pLeftIndex, pRightIndex, nLeftIndex, nRightIndex;
    preSort(arr, pLeftIndex, pRightIndex, nLeftIndex, nRightIndex);
    bSort(arr, pLeftIndex, pRightIndex, eldestBit);
    bSort(arr, nLeftIndex, nRightIndex, eldestBit);
}

double getTimeOfSort(std::vector<int> &arr, int arrSize, int eldestBit)
{
    auto start = std::chrono::high_resolution_clock::now();
    bitwiseSort(arr, eldestBit);
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
        int i, eldestBit = getEldestBit(arr);
        double averageTime = 0;
        for (i = 0; i < 3; ++i)
        {
            int arrSize = arr.size();
            averageTime += getTimeOfSort(arr, arrSize, eldestBit);
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
