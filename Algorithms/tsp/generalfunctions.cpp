#include <time.h>
#include <cstdlib>
#include <iostream>

void Swap(int &x, int &y)
{
    int tmp = x; x = y; y = tmp;
}

void getCopyArray(int *arr1, int *arr2, int n)
{
    for(int i = 0; i < n; i++) arr2[i] = arr1[i];
}

void bubbleSortUp(int *a, int n, int g)
{
    for(int k = n - 1; k > g; k--)
    {
        for(int i = g; i < k; i++)
            if(a[i] > a[i + 1])
                Swap(a[i], a[i + 1]);
    }
}

void randInput(int **matrix, int n, int left = 1, int right = 20)
{
    int i, j;
    matrix[0][0] = 0;
    for (i = 1; i <= n; i++)
        matrix[0][i]= i;
    for (i = 1; i <= n; i++)
        matrix[i][0] = i;
    srand(time(0));
    for(i = 1; i <= n; i++)
    for(j = 1; j <= n; j++)
    {   if (i == j) matrix[i][j] = 0;
        else
            matrix[i][j] = rand()%right + left;
            }
}

void inputMatrix(int **matrix, int n)
{
    int i, j;
    matrix[0][0] = 0;
    for (i = 1; i <= n; i++)
        matrix[0][i]= i;
    for (i = 1; i <= n; i++)
        matrix[i][0] = i;
    for(i = 1; i <= n; i++)
    for(j = 1; j <= n; j++)
    {std::cin >> matrix[i][j];}
}

void outputMatrix(int **matrix, int n)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j=0; j <= n; j++)
            std::cout << matrix[i][j] << '\t';
        std::cout << std::endl;
    }
}

void outputPath(int *path, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << path[i] << ' ';
    std::cout << std::endl;
}

int getCostOfPath(int **matrix, int n, int *path)
{
    int k, cost=0;
    for(k = 0; k < n - 1; k++) cost+=matrix[path[k]][path[k + 1]];
    std::cout << "Стоимость: " << cost << std::endl;
    return cost;
}

//Устанавливает первоначальное значение пути
void setPath(int *path, int *finalPath, int startTown, int numberOfTowns)
{
    int i, j;
    path[0] = startTown;
    finalPath[0] = startTown;
    for (i = 1, j = 1; i < numberOfTowns; i++, j++)
    {
        if (i == startTown) j++;
            {
                path[i] = j;
                finalPath[i] = j;
            }

    }
}
