#include <iostream>
#include <vector>
#include "generalfunctions.h"
#include "/home/rin/Labs/OOP/BoolVector/BoolVector.h"

bool isTSorted(std::vector<int> &result, BoolMatrix &matrix, const int vertexNumber)
{
    BoolVector definedVertexes(vertexNumber, false), noAncestorVertexes(vertexNumber, false);
    for (int j = 0; j < vertexNumber && definedVertexes.getWeight() != definedVertexes.length(); ++j)
    {
        noAncestorVertexes = ~definedVertexes & ~matrix.rowsDisjunction();
        definedVertexes |= noAncestorVertexes;
        for (int i = 0; i < vertexNumber; ++i)
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
    int vertexNumber = 7;
    BoolMatrix matrix = createMatrix(vertexNumber);
    std::vector<int> result;
    if (!isTSorted(result, matrix, vertexNumber))
    {
        std::cout << "Graph has cycle, no answer\n";
    }
    else
    {
        for (int i = 0; i < vertexNumber; ++i)
        {
            std::cout << result[i];
        }
    }
    return 0;
}
