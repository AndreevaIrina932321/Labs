#include <iostream>
#include <chrono>
#include "generalfunctions.h"

void getNewPath(int *path, int n)
{
   int i, j, temp;
    for(i = n - 2; i > 0; i--)
    {if (path[i] < path[i+1])
    {
        for(j = n - 1; j > i; j--)
        {
            if(path[i] < path[j])
            {
                Swap(path[i], path[j]);
                break;
                }
        }
        break;
    }}
    bubbleSortUp(path, n, i + 1);
    outputPath(path, n);
}


void djkstraAlgorithm(int **matrix, int *path, int *finalPath, int &minC, int &maxC, int k, int n)
{
    int cost;
    for (int i = 0; i < k - 1; i++)
    {
        getNewPath(path, n);
        cost = getCostOfPath(matrix, n, path);
        if (minC > cost)
        {
            minC = cost;
            getCopyArray(path, finalPath, n);
        }
        if (maxC < cost)
        {
            maxC = cost;
        }
    }
}

int main()
{
    int numberOfTowns, startTown, i, j, p = 1, minCost = 0, maxCost = 0;
    std::cout << "Введите количество городов, которые необходимо посетить :";
    std::cin >> numberOfTowns;
    numberOfTowns=std::abs(numberOfTowns);
    if (numberOfTowns == 0)
        ++numberOfTowns;
    do {
    std::cout << "Введите номер начального города (он не может быть больше их количества):";
    std::cin >> startTown;} while (startTown>numberOfTowns || startTown<1);
    int *path = new int[numberOfTowns];
    int *finalPath = new int [numberOfTowns];
    int **matCost = new int* [numberOfTowns+1];
    for (i = 0; i <= numberOfTowns; i++)
        matCost[i] = new int [numberOfTowns+1];
    randInput(matCost, numberOfTowns);
    setPath(path, finalPath, startTown, numberOfTowns);
    //inputMatrix(matCost, numberOfTowns);
    outputPath(path, numberOfTowns);
    minCost = getCostOfPath(matCost, numberOfTowns, path);
    for (i = 1; i < numberOfTowns; i++) p *= i;
    const auto start = std::chrono::high_resolution_clock::now();
    djkstraAlgorithm(matCost, path, finalPath, minCost, maxCost, p, numberOfTowns);
    const auto end = std::chrono::high_resolution_clock::now();
    outputMatrix(matCost, numberOfTowns);
    std::cout << "Минимальная стоимость: " << minCost << std::endl;
    std::cout << "Оптимальный путь: ";
    outputPath(finalPath, numberOfTowns);
    const std::chrono::duration<double> diff = end - start;
    //std::cout << "Time " << diff << '\n';
    for (i = 0; i <= numberOfTowns; i++)
        delete [] matCost[numberOfTowns+1];
    delete [] path;
    delete [] finalPath;
    return 0;
}
