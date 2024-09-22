#ifndef GENERALFUNCTIONS_H_INCLUDED
#define GENERALFUNCTIONS_H_INCLUDED


void Swap(int &x, int &y);
void getCopyArray(int *arr1, int *arr2, int n);
void bubbleSortUp(int *a, int n, int g);
void randInput(int **matrix, int n, int left = 1, int right = 20);
void inputMatrix(int **matrix, int n);
void outputMatrix(int **matrix, int n);
void outputPath(int *path, int n);
int getCostOfPath(int **matrix, int n, int *path);
void setPath(int *path, int *finalPath, int startTown, int numberOfTowns);

#endif // GENERALFUNCTIONS_H_INCLUDED
