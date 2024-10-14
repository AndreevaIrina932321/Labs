#include <fstream>

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
    if (file.is_open())
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
    std::ofstream file("arrays.txt", std::ios_base::out);

    int *arr1 = new int [size1];
    int *arr2 = new int [size2];
    int *arr3 = new int [size3];
    for (int i = 0; i < 3; ++i)
    {
        randInput(arr1, size1, -range, range);
        writeArray(arr1, size1, file);
        randInput(arr2, size2, -range, range);
        writeArray(arr2, size2, file);
        randInput(arr3, size3, -range, range);
        writeArray(arr3, size3, file);
        range *= 100;
    }
    file.close();
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
}
