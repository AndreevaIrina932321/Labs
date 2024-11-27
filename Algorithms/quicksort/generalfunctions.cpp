#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

void randInput(int *arr, int sizeOfArray, int left = -10, int right = 10)
{
    int i;
    for (i = 0; i < sizeOfArray; ++i)
    {
        arr[i] = rand() % (right - left) + left;
    }
}

void writeArray(int *arr, int sizeOfArray, std::ofstream &file)
{
    if (file.is_open()) //try catch
    {
        for (int i = 0; i < sizeOfArray; ++i)
        {
            file << arr[i] << ' ';
        }
        file << std::endl;
    }
}

void saveArrays()
{
    const int size1 = 5, size2 = 8, size3 = 10;
    int range = 10;
    std::ofstream fileOut("arrays.txt", std::ios_base::out);

    int *arr1 = new int [size1];
    int *arr2 = new int [size2];
    int *arr3 = new int [size3];
    for (int i = 0; i < 3; ++i)
    {
        randInput(arr1, size1, -range, range);
        writeArray(arr1, size1, fileOut);
        randInput(arr2, size2, -range, range);
        writeArray(arr2, size2, fileOut);
        randInput(arr3, size3, -range, range);
        writeArray(arr3, size3, fileOut);
        range *= 100;
    }
    fileOut.close();
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
}

bool isSorted(const std::vector<int> &arr)
{
    int arraySize = arr.size();
    for (int i = 0; i < arraySize - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

bool readArray(std::vector<int> &arr, std::ifstream &fileIn)
{
    bool isEmpty;
    std::string line;
    std::string number;
    arr.clear();
    if (fileIn.is_open()) //try catch
    {
        isEmpty = static_cast<bool>(std::getline(fileIn, line));
        std::stringstream strStream(line);
        while (std::getline(strStream, number, ' '))
        {
            arr.push_back(atoi(number.c_str()));
        }
    }
    return isEmpty;
}

void printArray(const std::vector<int> &arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}
