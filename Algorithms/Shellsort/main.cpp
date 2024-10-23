#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <assert.h>
#include <math.h>
#include "generalfunctions.h"

void setGapSequenceShell(std::vector<int> &gap, int arrSize)
{
    for (int gapValue = 1; gapValue <= arrSize / 2 ; gapValue *= 2)
    {
        gap.push_back(gapValue);
    }
}

void setGapSequenceKnuth(std::vector<int> &gap, int arrSize)
{
    for (int gapValue = 1; gapValue <= arrSize; gapValue = 3 * gapValue + 1)
    {
        gap.push_back(gapValue);
    }
    if (gap[gap.size() - 1] >= arrSize)
    {
        gap.erase(gap.end() - 1);
    }
}

void setGapSequenceSedgewick(std::vector<int> &gap, int arrSize)
{
    int gapValue = 1;
    for (int j = 0; gapValue < arrSize; ++j)
    {
        if (j % 2)
        {
            gapValue = 8 * std::pow(2, j) - 6 * pow(2, (j + 1) / 2) + 1;
        }
        else
        {
            gapValue = 9 * std::pow(2 , j) - 9 * std::pow(2, j / 2) + 1;
        }
        gap.push_back(gapValue);
    }
    if (gap[gap.size() - 1] >= arrSize)
    {
        gap.erase(gap.end() - 1);
    }
}

void ShellSort(std::vector<int> &arr, std::vector<int> &gap)
{
    int arraySize = arr.size();
    int gapSize = gap.size();
    int gapCounter, arrCounter, gapValue , leftArrPos, unsValueCopy, k;
    for (gapCounter = gapSize - 1; gapCounter >= 0; --gapCounter)
    {
        gapValue = gap[gapCounter];
        for (leftArrPos = 0; leftArrPos < gapValue; ++leftArrPos)
        {
            for (arrCounter = leftArrPos + gapValue; arrCounter < arraySize; arrCounter += gapValue)
            {
                unsValueCopy = arr[arrCounter];

                for (k = arrCounter - gapValue; k >= 0 && arr[k] > unsValueCopy; k -= gapValue)
                {
                    arr[k + gapValue] = arr[k];
                }
                arr[k + gapValue] = unsValueCopy;
            }
        }
    }
}

double getTimeOfSort(std::vector<int> &arr, std::vector<int> &arrCopy, std::vector<int> &gap, int arrSize)
{
        auto start = std::chrono::high_resolution_clock::now();
        ShellSort(arr, gap);
        auto end = std::chrono::high_resolution_clock::now();
        assert(isSorted(arr));
        arr = arrCopy;
        gap.clear();
        std::chrono::duration<double> diff = end - start;
        return diff.count();
}

int main()
{
    std::ifstream fileIn("arrays.txt");
    std::vector<int> arr;
    double averageShellTime = 0, averageKnuthTime = 0, averageSedgewickTime = 0;
    for (int j = 0; j < 9; ++j)
    {
        int i;
        readArray(arr, fileIn);
        for (i = 0 ; i < 3; ++i)
        {
            std::vector<int> arrCopy(arr);
            int arrSize = arr.size();
            std::vector<int> gap;

            setGapSequenceShell(gap, arrSize);
            averageShellTime += getTimeOfSort(arr, arrCopy, gap, arrSize);

            setGapSequenceKnuth(gap, arrSize);
            averageKnuthTime += getTimeOfSort(arr, arrCopy, gap, arrSize);

            setGapSequenceSedgewick(gap, arrSize);
            averageSedgewickTime += getTimeOfSort(arr, arrCopy, gap, arrSize);
        }
        std::cout << "Среднее время для последовательности Шелла: " << averageShellTime / i <<"s\n";
        std::cout << "Среднее время для последовательности Кнута: " << averageKnuthTime / i <<"s\n";
        std::cout << "Среднее время для последовательности Сэджвика: " << averageSedgewickTime / i <<"s\n";
        std::cout << std::endl;
    }
    fileIn.close();
    return 0;
}
