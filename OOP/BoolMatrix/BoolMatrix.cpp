#include <assert.h>
#include <iostream>
#include "BoolMatrix.h"
#include "../BoolVector/BoolVector.cpp"
#include "../Array/Array.cpp"

BoolMatrix::BoolMatrix(const int rowsCount, const int columnCount, const bool value)
{
    assert(columnCount >= 0 && rowsCount >= 0);
    BoolVector sample(columnCount, value);
	m_columnsCount = columnCount;
	m_rowsCount = rowsCount;
	m_rows = Array<BoolVector>(rowsCount, sample);
}

BoolMatrix::BoolMatrix(char **sample, const int rowsCount, const int length)
{
    assert(length >= 0 && rowsCount >= 0);
    m_columnsCount = length;
    m_rowsCount = rowsCount;
    m_rows = Array<BoolVector>(rowsCount);
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

int BoolMatrix::collumnWeight(int collumnIndex) const
{
    assert(collumnIndex >= 0 && collumnIndex < m_columnsCount);
    int weight = 0;
    for (int i = 0; i < m_rowsCount; ++i)
    {
        if (m_rows[i].bitValue(collumnIndex))
        {
            ++weight;
        }
    }
    return weight;
}

BoolVector BoolMatrix::rowsConjunction() const
{
    assert(m_rowsCount > 0);
    BoolVector result(m_rows[0]);
    for (int i = 1; i < m_rowsCount; ++i)
    {
        result &= m_rows[i];
    }
    return result;
}

BoolVector BoolMatrix::rowsDisjunction() const
{
    assert(m_rowsCount > 0);
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

BoolVector &BoolMatrix::operator[](int index)
{
    assert(index >= 0 && index < m_rowsCount);
    return m_rows[index];
}

const BoolVector &BoolMatrix::operator[](const int index) const
{
    assert(index >= 0 && index < m_rowsCount);
    return m_rows[index];
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix &other) const
{
    int i = 0, minRowsCounter = std::min(m_rowsCount, other.m_rowsCount);
    int maxRowsCounter = std::max(m_rowsCount, other.m_rowsCount);
    BoolMatrix result(maxRowsCounter, m_columnsCount);
    for (i = 0; i < minRowsCounter; ++i)
    {
        result.m_rows[i] = m_rows[i] & other.m_rows[i];
    }
    for (; i < maxRowsCounter; ++i)
    {
        result.m_rows[i].setAll(false);
    }
    return result;
}

BoolMatrix &BoolMatrix::operator&=(const BoolMatrix &other)
{
    operator&(other).swap(*this);
    return *this;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix &other) const
{
    int i, minRowsCounter = std::min(m_rowsCount, other.m_rowsCount);
    BoolMatrix result = m_rowsCount < other.m_rowsCount ? other : *this;
    for (i = 0; i < minRowsCounter; ++i)
    {
        result.m_rows[i] = m_rows[i] | other.m_rows[i];
    }
    return result;
}

BoolMatrix &BoolMatrix::operator|=(const BoolMatrix &other)
{
    operator|(other).swap(*this);
    return *this;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix &other) const
{
    int i, minRowsCounter = std::min(m_rowsCount, other.m_rowsCount);
    BoolMatrix result(other);
    result = m_rowsCount < other.m_rowsCount ? other : *this;
    for (i = 0; i < minRowsCounter; ++i)
    {
        result.m_rows[i] = m_rows[i] ^ other.m_rows[i];
    }
    return result;
}

BoolMatrix &BoolMatrix::operator^=(const BoolMatrix &other)
{
    operator^(other).swap(*this);
    return *this;
}

BoolMatrix BoolMatrix::operator~() const
{
    BoolMatrix result(*this);
    for (int i = 0; i < result.m_rowsCount; ++i)
    {
        result.m_rows[i].invertAll();
    }
    return result;
}

std::ostream& operator<<(std::ostream &out, const BoolMatrix &bm)
{
    if (!bm.getRowsNumber())
    {
        out << "boolean matrix is empty\n";
    }

    else
    {
         out << "[\n";
        for (int i = 0; i < bm.getRowsNumber(); ++i)
        {
            out << bm[i];
        }
        out << "]\n";
    }
    return out;
}

std::istream& operator>>(std::istream &in, BoolMatrix &bm)
{
    for (int i = 0; i < bm.getRowsNumber(); ++i)
    {
        in >> bm[i];
    }
    return in;
}
