#include <assert.h>
#include <iostream>
#include "BoolVector.h"

BoolVector::BoolVector(int length)
	: m_length(length)
{
    assert(length >= 0);
	m_cellCount = m_length / CellSize;
	if (m_length % CellSize != 0)
	{
		m_cellCount++;
	}

	m_cells = new Cell[m_cellCount];
}

BoolVector::BoolVector(int length, bool value)
	: BoolVector(length)
{
	Cell sample = 0;
	if (value)
	{
        sample = ~sample;
	}
	for (int i = 0; i < length / CellSize + (length % CellSize != 0); ++i)
	{
        m_cells[i] = sample;
	}

}

BoolVector::BoolVector(const char *arr, const int size)
{
    assert(size >= 0);
    if (arr == nullptr)
    {
        std::cerr << "BoolVector::BoolVector: can't create BoolVector from void array, BoolVector will be default...\n";
        m_length = 0;
        m_cells = nullptr;
        m_cellCount = 0;
    }
    else
    {
        m_cellCount = size;
        m_length = m_cellCount * CellSize;
        m_cells = new Cell[m_cellCount];
        for (int i = 0; i < size; ++i)
        {
            m_cells[i] = arr[i];
        }
    }
}

BoolVector::BoolVector(const BoolVector &other)
    : m_cellCount(other.m_cellCount), m_length(other.m_length)
{
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; ++i)
    {
        m_cells[i] = other.m_cells[i];
    }
}

BoolVector::~BoolVector()
{
	delete[] m_cells;
}

bool BoolVector::bitValue(int index) const
{
	assert(index >= 0 && index < m_length);
	Cell mask = _mask(index);
	return m_cells[index / CellSize] & mask;
}

void BoolVector::setBitValue(int index, bool value)
{
	assert(index >= 0 && index < m_length);
	Cell mask = _mask(index);
	if (value)
	{
		m_cells[index / CellSize] |= mask;
	}
	else
	{
		m_cells[index / CellSize] &= ~mask;
	}
}

void BoolVector::swap(BoolVector &other) noexcept
{
    std::swap(m_length, other.m_length);
    std::swap(m_cellCount, other.m_cellCount);
    std::swap(m_cells, other.m_cells);
}

BoolVector &BoolVector::operator=(const BoolVector& other)
{
	if (this == &other)
    {
        return *this;
    }

    if (m_length == other.m_length)
    {
        for (int i = 0; i < m_cellCount; ++i)
        {
            m_cells[i] = other.m_cells[i];
        }
    }
    else
    {
        BoolVector vectorCopy(other);
        swap(vectorCopy);
    }
	return *this;
}

BoolVector::Rank BoolVector::operator[](int index)
{
    assert(index >= 0 && index < m_length);
    return Rank(&m_cells[index / CellSize], _mask(index));
}

int BoolVector::_excessRankCount() const
{
	return (m_cellCount * CellSize - m_length);
}

void BoolVector::print() const
{
    if (m_length == 0)
    {
        std::cout << "boolean vector is empty\n";
    }
    else
    {
        for (int i = 0; i < m_length - 1; ++i)
        {
            std::cout << bitValue(i);
        }
        std::cout << bitValue(m_length - 1) << '\n';
    }
}

void BoolVector::input()
{
    std::cout << "Введите количество бит";
    std::cin >> m_length;
    if (m_length < 0)
    {
         std::cerr << "Array::Array: size is negative, invert...\n";
         m_length = -m_length;
    }
    m_cellCount = m_length / CellSize;
    if (m_length % CellSize != 0)
	{
		m_cellCount++;
	}
	delete [] m_cells;
	m_cells = new Cell[m_cellCount];
	std::cout << "Введите булев вектор: ";
	bool value;
	for (int i = 0; i < m_length; ++i)
	{
        std::cin >> value;
        setBitValue(i, value);
	}
}

void BoolVector::invertAll()
{
    for (int i = 0; i < m_cellCount; ++i)
    {
        m_cells[i] = ~m_cells[i];
    }
}

bool BoolVector::invert(const int index)
{
    if (index < 0 || index > m_length)
    {
        std::cerr << "BoolVector::invert: incorrect index...\n";
        return false;
    }
    setBitValue(index, !bitValue(index));
    return true;
}

void BoolVector::setBits(int index, int amount, bool value)
{
    assert(index >= m_length);
    if (index < 0)
    {
        std::cerr << "BoolVector::setBits: incorrect index...\n";
        index = 0;
    }
    if (index + amount >= m_length)
    {
        std::cerr << "BoolVector::setBits: incorrect amount...\n";
        amount = m_length - index - 1;
    }
    for (int i = index, j = 0; j < amount; ++i, ++j)
    {
        invert(i);
    }
}

void BoolVector::setAll(bool value)
{
    BoolVector copyVector(m_length, value);
    swap(copyVector);
}

int BoolVector::getWeight() const
{
    int weight = 0;
    for (int i = 0; i < m_length; ++i)
    {
        if (Rank(&m_cells[i / CellSize], _mask(i)))
        {
            ++weight;
        }
    }
    return weight;
}

BoolVector::Cell BoolVector::_mask(int index)
{
    Cell mask = 1;
    mask <<= CellSize - 1 - (index % CellSize);
    return mask;
}

BoolVector::Rank::Rank(Cell *cell, Cell mask)
    : m_cell(cell), m_mask(mask)
{
    assert(m_cell != nullptr);
    assert(m_mask > 0);
}

BoolVector::Rank& BoolVector::Rank::operator=(const bool value)
{
    if (value)
    {
        *m_cell |= m_mask;
    }
    else
    {
        *m_cell &= ~m_mask;
    }
    return *this;
}

BoolVector::Rank& BoolVector::Rank::operator=(const Rank &other)
{
    if (bool(other))
    {
        *m_cell |= m_mask;
    }
    else
    {
        *m_cell &= ~m_mask;
    }
    return *this;
}

BoolVector::Rank::operator bool() const
{
    return (*m_cell & m_mask) != 0;
}

BoolVector BoolVector::operator&(const BoolVector &other) const
{
    BoolVector result(std::max(m_length, other.m_length));
    int i;
    for (i = 0; i < m_length; ++i)
    {
        result.setBitValue(i, bitValue(i) && other.bitValue(i));
    }
    for (; i < result.length(); ++i)
    {
        result.setBitValue(i, false);
    }
    return result;
}

/*BoolVector BoolVector::operator&(const BoolVector &other) const
{
    BoolVector result(std::max(m_length, other.m_length));
    int i, minLength = std::min(m_length, other.m_length);
    for (i = 0; i < minLength / CellSize; ++i)
    {
        result.m_cells[i] = m_cells[i] & other.m_cells[i];
    }
    i *= CellSize;
    for (; i < minLength; ++i)
    {
         result.setBitValue(i, bitValue(i) && other.bitValue(i));
    }
    for (; i < result.m_length; ++i)
    {
        result.setBitValue(i, false);
    }
    return result;
}*/

BoolVector &BoolVector::operator&=(const BoolVector &other)
{
    operator&(other).swap(*this);
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector &other) const
{
    BoolVector result(std::max(m_length, other.m_length));
    int i = 0;
    for (i = 0; i < m_length; ++i)
    {
        result.setBitValue(i, bitValue(i) || other.bitValue(i));
    }
    for (; i < result.length(); ++i)
    {
        result.setBitValue(i, other.bitValue(i));
    }
    return result;
}

BoolVector &BoolVector::operator|=(const BoolVector &other)
{
    operator|(other).swap(*this);
    return *this;
}

BoolVector BoolVector::operator^(const BoolVector &other) const
{
    BoolVector result(std::max(m_length, other.m_length));
    int i = 0;
    for (i = 0; i < m_length; ++i)
    {
        result.setBitValue(i, bitValue(i) ^ other.bitValue(i));
    }
    for (; i < result.length(); ++i)
    {
        result.setBitValue(i, other.bitValue(i));
    }
    return result;
}

BoolVector &BoolVector::operator^=(const BoolVector &other)
{
    operator^(other).swap(*this);
    return *this;
}

BoolVector BoolVector::operator<<(int position) const
{
    BoolVector result(*this);
    int i;
    if (position >= m_length)
    {
        result.setAll(false);
        return result;
    }
    for (i = 0; position + i < result.m_length; ++i)
    {
        result.setBitValue(i, result.bitValue(position + i));
    }
    for (; i < result.m_length; ++i)
    {
        result.setBitValue(i, false);
    }
    return result;
}

BoolVector &BoolVector::operator<<=(int position)
{
    operator<<(position).swap(*this);
    return *this;
}
BoolVector BoolVector::operator>>(int position) const
{
    BoolVector result(*this);
    int i;
    if (position >= m_length)
    {
        result.setAll(false);
        return result;
    }
    for (i = result.m_length - 1; i >= position; --i)
    {
        result.setBitValue(i, result.bitValue(i - position));
    }
    for (; i >= 0; --i)
    {
        result.setBitValue(i, false);
    }
    return result;
}

BoolVector &BoolVector::operator>>=(int position)
{
    operator>>(position).swap(*this);
    return *this;
}

BoolVector BoolVector::operator~() const
{
    BoolVector result(*this);
    result.invertAll();
    return result;
}

BoolVector::Rank BoolVector::Rank::operator&(const bool value) const
{
    Rank result = *this;
    if (value)
    {
        *result.m_cell &= m_mask;
    }
    else
    {
        result = 0;
    }
    return result;
}

BoolVector::Rank BoolVector::Rank::operator&(const Rank &other) const
{
    Rank result = operator&(bool(other));
    return result;
}

BoolVector::Rank BoolVector::Rank::operator|(const bool value) const
{
    Rank result = *this;
    if (value)
    {
        result = 1;
    }
    return result;
}

BoolVector::Rank BoolVector::Rank::operator|(const Rank &other) const
{
    Rank result = operator|(bool(other));
    return result;
}

BoolVector::Rank BoolVector::Rank::operator^(const bool value) const
{
    Rank result = *this;
    result = value ^ bool(*this);
    return result;
}

BoolVector::Rank BoolVector::Rank::operator^(const Rank &other) const
{
    Rank result = operator^(bool(other));
    return result;
}

BoolVector::Rank &BoolVector::Rank::operator&=(const bool value)
{
    operator&(value).swap(*this);
    return *this;
}

BoolVector::Rank &BoolVector::Rank::operator&=(const Rank &other)
{
    operator&(other).swap(*this);
    return *this;
}

BoolVector::Rank &BoolVector::Rank::operator|=(const bool value)
{
    operator|(value).swap(*this);
    return *this;
}

BoolVector::Rank &BoolVector::Rank::operator|=(const Rank &other)
{
    operator&(other).swap(*this);
    return *this;
}

BoolVector::Rank &BoolVector::Rank::operator^=(const bool value)
{
    operator^(value).swap(*this);
    return *this;
}

BoolVector::Rank &BoolVector::Rank::operator^=(const Rank &other)
{
    operator&(other).swap(*this);
    return *this;
}

BoolVector::Rank BoolVector::Rank::operator~() const
{
    Rank result = *this;
    if (bool(result))
    {
        result = 0;
    }
    else
    {
        result = 1;
    }
    return result;
}

void BoolVector::Rank::swap(Rank &other) noexcept
{
    std::swap(m_cell, other.m_cell);
    std::swap(m_mask, other.m_mask);
}
