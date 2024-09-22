#include <iostream>
#include <chrono>
#include <time.h>
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
        if (maxC <= cost)
        {
            maxC = cost;
        }
        if (minC > cost)
        {
            minC = cost;
            getCopyArray(path, finalPath, n);
        }
    }
}




bool inCycle(int *path, int k, int index)
{
    for (int i = 0; i < k; i++)
        if(path[i] == index)
            return 0;
    return 1;
}

int getMinElement(int *row, int *path, int n, int position)
{
    int minInd=0;
    //while (InCycle())
    row[0]=1000;
    for (int i = 1; i <= n ; i++)
    {
        if (row[minInd] > row[i] && row[i] != -1 && inCycle(path, position, i)) minInd = i;
    }
    return minInd;
}


int greedyAlgorithm(int **matrix, int *path, int n)
{
    int i, cost = 0, town = path[0];
    for (i = 1; i < n; i++)
    {
        town = getMinElement(matrix[town], path, n, i);
        path[i] = town;
        cost += matrix[path[i - 1]][town];
    }
    return cost;
}

int main()
{
    int numberOfTowns, startTown, i, j, p = 1, minCost = 0, maxCost = 0, gminCost;
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
    maxCost = minCost;
    for (i = 1; i < numberOfTowns; i++) p *= i;
    auto start = std::chrono::high_resolution_clock::now();
    djkstraAlgorithm(matCost, path, finalPath, minCost, maxCost, p, numberOfTowns);
    auto end = std::chrono::high_resolution_clock::now();
    outputMatrix(matCost, numberOfTowns);
    std::cout << "Минимальная стоимость: " << minCost << std::endl;
    std::cout << "Максимальная стоимость: " << maxCost << std::endl;
    std::cout << "Оптимальный путь: ";
    outputPath(finalPath, numberOfTowns);
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    std::cout << "Time " << diff.count() << "ms\n";
    start = std::chrono::high_resolution_clock::now();
    gminCost = greedyAlgorithm(matCost, finalPath, numberOfTowns);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Минимальная стоимость: " << gminCost << std::endl;
    std::cout << "Оптимальный путь: ";
    outputPath(finalPath, numberOfTowns);
    diff = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    std::cout << "Time " << diff.count() << "ms\n";
    for (i = 0; i <= numberOfTowns; i++)
        delete [] matCost[numberOfTowns+1];
    delete [] path;
    delete [] finalPath;
    return 0;
}
