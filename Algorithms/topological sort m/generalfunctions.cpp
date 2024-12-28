#include "generalfunctions.h"
#include "/home/rin/Labs/OOP/BoolMatrix/BoolMatrix.cpp"

BoolMatrix createMatrix(const int vertexAmount)
{
    BoolMatrix matrix(vertexAmount, vertexAmount, false);
    matrix.setBit(1, 0, true);
    matrix.setBit(3, 4, true);
    matrix.setBit(4, 0, true);
    matrix.setBit(4, 2, true);
    matrix.setBit(5, 1, true);
    matrix.setBit(5, 2, true);
    matrix.setBit(5, 4, true);
    matrix.setBit(6, 0, true);
    return matrix;
}

