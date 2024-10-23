#pragma once
#include <vector>
#include <fstream>

void randInput(int *arr, int sizeOfArray, int left = -10, int right = 10);
void writeArray(int *arr, int sizeOfArray, std::ofstream &file);
void saveArrays();
bool isSorted(const std::vector<int> &arr);
void readArray(std::vector<int> &arr, std::ifstream &fileIn);


