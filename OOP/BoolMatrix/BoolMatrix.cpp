#include <assert.h>
#include <iostream>
#include "BoolMatrix.h"
#include "/home/rin/Labs/OOP/BoolVector/BoolVector.cpp"
#include "/home/rin/Labs/OOP/Array/Array.cpp"

BoolMatrix::BoolMatrix(const int columnCount, const int rowsCount, const bool value)
{
    assert(columnCount >= 0 && rowsCount >= 0);
    BoolVector sample(columnCount, value);
	m_columnsCount = columnCount;
	m_rowsCount = rowsCount;
	m_rows = Array<BoolVector>(columnCount, sample);
}

BoolMatrix::BoolMatrix(char **sample, const int rowsCount, const int length)
{
    assert(length >= 0 && rowsCount >= 0);
    m_columnsCount = length * CellSize;
    m_rowsCount = rowsCount;
    for (int i = 0; i < m_rowsCount; ++i)
    {
        BoolVector row(sample[i], length);
        m_rows[i] = row;
    }
}

BoolMatrix::BoolMatrix(const BoolMatrix &other)
{
    m_columnsCount = other.m_columnsCount;
    m_rowsCount = other.m_rowsCount;
    m_rows = other.m_rows;
}

void BoolMatrix::swap(BoolMatrix &other) noexcept
{
    std::swap(m_columnsCount, other.m_columnsCount);
    std::swap(m_rowsCount, other.m_rowsCount);
    m_rows.swap(other.m_rows);
}

void BoolMatrix::print() const
{
    for (int i = 0; i < m_rowsCount; ++i)
    {
        m_rows[i].print();
    }
}

void BoolMatrix::input()
{
    std::cout << "Введите количество строк: ";
    std::cin >> m_rowsCount;
    if (m_rowsCount < 0)
    {
         std::cerr << "BoolMatrix::input(): rows number is negative, invert...\n";
         m_rowsCount = -m_rowsCount;
    }
    std::cout << "Введите колиичество столбцов: ";
    std::cin >> m_columnsCount;
    if (m_columnsCount < 0)
    {
         std::cerr << "BoolMatrix::input(): columns number is negative, invert...\n";
         m_columnsCount = -m_columnsCount;
    }
    std::cout << "Введите булеву матрицу:" << std::endl;
    for (int i = 0; i < m_rowsCount; ++i)
    {
        m_rows[i].input();
    }
}

int BoolMatrix::getWeight() const
{
    int weight = 0;
    for (int i = 0; i < m_rowsCount; ++i)
    {
        weight += m_rows[i].getWeight();
    }
    return weight;
}

int BoolMatrix::rowWeight(int rowIndex) const
{
    assert(rowIndex >= 0 && rowIndex < m_rowsCount);
    return m_rows[rowIndex].getWeight();
}

BoolVector BoolMatrix::rowsConjunction() const
{
    BoolVector result(m_rows[0]);
    for (int i = 1; i < m_rowsCount; ++i)
    {
        result &= m_rows[i];
    }
    return result;
}

BoolVector BoolMatrix::rowsDisjunction() const
{
    BoolVector result(m_rows[0]);
    for (int i = 1; i < m_rowsCount; ++i)
    {
        result |= m_rows[i];
    }
    return result;
}

void BoolMatrix::setBit(const int rowIndex, const int columnIndex, const bool value)
{
    assert(rowIndex >= 0 && rowIndex < m_rowsCount);
    m_rows[rowIndex].setBitValue(columnIndex, value);
}

void BoolMatrix::setSequence(const int rowIndex, const int columnIndex, const int amount, const bool value)
{
    assert(rowIndex >= 0 && rowIndex < m_rowsCount);
    m_rows[rowIndex].setBits(columnIndex, amount,  value);
}

bool BoolMatrix::invertBit(const int rowIndex, const int columnIndex)
{
    if (rowIndex >= 0 && rowIndex < m_rowsCount)
    {
        return false;
    }
    return m_rows[rowIndex].invert(columnIndex);
}

void BoolMatrix::invertSequence(const int rowIndex, const int columnIndex, const int amount)
{
    assert(rowIndex >= 0 && rowIndex < m_rowsCount && amount >= 0);
    for (int i = 0; i < amount; ++i)
    {
        if (m_rows[rowIndex].invert(columnIndex + i) == false)
        {
            break;
        }
    }
}

BoolMatrix &BoolMatrix::operator=(const BoolMatrix &other)
{
    if (this == &other)
    {
        return *this;
    }

    else
    {
        BoolMatrix matrixCopy(other);
        swap(matrixCopy);
    }

	return *this;
}

BoolVector BoolMatrix::operator[](int index)
{
    assert(index >= 0 && index < m_rowsCount);
    return m_rows[index];
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix &other) const
{
    BoolMatrix result();
    if (m_rowsCount < other.m_rowsCount)
    {
        for (int i = 0; i < m_rowsCount; ++i)
        {

        }
    }
}

BoolMatrix &BoolMatrix::operator&=(const BoolMatrix &other)
{

}

BoolMatrix BoolMatrix::operator|(const BoolMatrix &other) const
{

}

BoolMatrix &BoolMatrix::operator|=(const BoolMatrix &other)
{

}

BoolMatrix BoolMatrix::operator^(const BoolMatrix &other) const
{

}

BoolMatrix &BoolMatrix::operator^=(const BoolMatrix &other)
{

}

BoolMatrix BoolMatrix::operator~() const
{

}
