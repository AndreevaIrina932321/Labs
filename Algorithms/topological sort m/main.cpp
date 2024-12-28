#include <iostream>
#include <vector>
#include "generalfunctions.h"
#include "/home/rin/Labs/OOP/BoolVector/BoolVector.h"

bool tSort(std::vector<int> &result, BoolMatrix &matrix, const int vertexAmount)
{
    BoolVector definedVertexes(vertexAmount, false), noAncestorVertexes(vertexAmount, false);
    for (int j = 0; j < vertexAmount && definedVertexes.getWeight() != definedVertexes.length(); ++j)
    {
        noAncestorVertexes = ~definedVertexes & ~matrix.rowsDisjunction();
        definedVertexes |= noAncestorVertexes;
        for (int i = 0; i < vertexAmount; ++i)
        {
            if(noAncestorVertexes.bitValue(i))
            {
                result.push_back(i + 1);
                matrix[i].setAll(false);
            }
        }
    }
    return definedVertexes.getWeight() == definedVertexes.length();
}

int main()
{
    int vertexAmount = 7;
    BoolMatrix matrix = createMatrix(vertexAmount);
    std::vector<int> result;
    if (!tSort(result, matrix, vertexAmount))
    {
        std::cout << "Graph has cycle, no answer\n";
    }
    else
    {
        for (int i = 0; i < vertexAmount; ++i)
        {
            std::cout << result[i];
        }
    }
    return 0;
}
