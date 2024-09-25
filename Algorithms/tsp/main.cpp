#include <iostream>
#include <chrono>
#include <ctime>
#include "generalfunctions.h"

bool getNewPath(int *path, int n)
{
    int i, j;
    for(i = n - 2; i > 0; i--)
    {
        if (path[i] < path[i + 1])
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
        }
    }
    bubbleSortUp(path, n, i + 1);
    if (i == 0)
        return 0;
    else
        return 1;
}


void djkstraAlgorithm(int **matrix, int *path, int *finalPath, int &minC, int &maxC, int n, bool flagD = 1)
{
    int cost;
    while (getNewPath(path, n))
    {
        cost = getCostOfPath(matrix, n, path);
        if (flagD)
        {
            outputPath(path, n);
            std::cout << "Стоимость: " << cost << std::endl;
        }

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
    int minInd = 1;
    while (!inCycle(path, position, minInd))
        ++minInd;
    for (int i = minInd + 1; i <= n ; i++)
    {
        if (row[minInd] > row[i] && inCycle(path, position, i)) minInd = i;
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


void getAllSolutions(int **matCost, int *path, int *finalPath, int numberOfTowns, int startTown)
{
    int minCost = 0, maxCost = 0, gminCost;
    float accuracy;
    //outputPath(path, numberOfTowns);
    minCost = getCostOfPath(matCost, numberOfTowns, path);
    maxCost = minCost;
    auto start = std::chrono::high_resolution_clock::now();
    djkstraAlgorithm(matCost, path, finalPath, minCost, maxCost, numberOfTowns, 0);
    auto end = std::chrono::high_resolution_clock::now();
    outputMatrix(matCost, numberOfTowns);
    std::cout << "Минимальная стоимость: " << minCost << std::endl;
    std::cout << "Максимальная стоимость: " << maxCost << std::endl;
    std::cout << "Оптимальный путь: ";
    outputPath(finalPath, numberOfTowns);
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time " << diff.count() << "s\n";
    start = std::chrono::high_resolution_clock::now();
    gminCost = greedyAlgorithm(matCost, finalPath, numberOfTowns);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Минимальная стоимость: " << gminCost << std::endl;
    std::cout << "Оптимальный путь: ";
    outputPath(finalPath, numberOfTowns);
    diff = end - start;
    std::cout << "Time " << diff.count() << "s\n";
    accuracy = (1 - (gminCost - minCost) / static_cast<float>(maxCost - minCost)) * 100;
    std::cout << "Качество решения: " << accuracy << '%' << std::endl;
}

int main()
{
    int numberOfTowns, startTown, i, j;
    std::cout << "Введите количество городов, которые необходимо посетить :";
    std::cin >> numberOfTowns;
    numberOfTowns = std::abs(numberOfTowns);
    if (numberOfTowns == 0)
        ++numberOfTowns;
    do
    {
        std::cout << "Введите номер начального города (он не может быть больше их количества):";
        std::cin >> startTown;
    }
    while (startTown > numberOfTowns || startTown < 1);

    int *path = new int[numberOfTowns];
    int *finalPath = new int [numberOfTowns];
    int **matCost = new int* [numberOfTowns + 1];
    for (i = 0; i <= numberOfTowns; i++)
        matCost[i] = new int [numberOfTowns + 1];
    srand(time(0));
    for (j = 0; j < 4; j++)
    {
        randInput(matCost, numberOfTowns);
        setPath(path, finalPath, startTown, numberOfTowns);
        getAllSolutions(matCost, path, finalPath, numberOfTowns, startTown);
    }
    for (i = 0; i <= numberOfTowns; i++)
        delete [] matCost[numberOfTowns + 1];
    delete [] matCost;
    delete [] path;
    delete [] finalPath;
    return 0;
}
