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

BoolVector::BoolVector(int length, const bool value)
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

BoolVector::BoolVector(const char *sample, const int sampleSize)
    : BoolVector(sample ? sampleSize : 0)
{
    for (int i = 0; i < sampleSize; ++i)
    {
        setBitValue(i, sample[i] - '0');
    }
}

BoolVector::BoolVector(const BoolVector &other)
    : BoolVector(other.m_length)
{
    for (int i = 0; i < m_cellCount; ++i)
    {
        m_cells[i] = other.m_cells[i];
    }
}

BoolVector::~BoolVector()
{
	delete[] m_cells;
}

bool BoolVector::bitValue(const int index) const
{
	assert(index >= 0 && index < m_length);
	Cell mask = _mask(index);
	return m_cells[index / CellSize] & mask;
}

void BoolVector::setBitValue(const int index, const bool value)
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

    if (m_cellCount == other.m_cellCount)
    {
        m_length = other.m_length;
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

BoolVector::Rank BoolVector::operator[](const int index)
{
    assert(index >= 0 && index < m_length);
    return Rank(&m_cells[index / CellSize], _mask(index));
}

const BoolVector::Rank BoolVector::operator[](const int index) const
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
        std::cerr << "BoolVector::invert: incorrect index, no changes...\n";
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
        std::cerr << "BoolVector::setBits: incorrect index, index will be 0...\n";
        index = 0;
    }
    if (index + amount >= m_length)
    {
        std::cerr << "BoolVector::setBits: incorrect amount, all bits after the index will be equal to value...\n";
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

BoolVector::Rank &BoolVector::Rank::operator=(const bool value)
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
    operator=(bool(other)).swap(*this);
    return *this;
}

BoolVector::Rank::operator bool() const
{
    return (*m_cell & m_mask) != 0;
}

BoolVector BoolVector::operator&(const BoolVector &other) const
{
    int minLength = std::min(m_length, other.m_length);
    BoolVector result(std::max(m_length, other.m_length), false);
    for (int i = 0; i < minLength; ++i)
    {
        result.setBitValue(result.m_length - i - 1, bitValue(m_length - i - 1) && other.bitValue(other.m_length - i - 1));
    }
    return result;
}

BoolVector &BoolVector::operator&=(const BoolVector &other)
{
    operator&(other).swap(*this);
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector &other) const
{
    int minLength = std::min(m_length, other.m_length);
    BoolVector result(*this);
    if (other.m_length > m_length)
    {
        result = other;
    }
    for (int i = 0; i < minLength; ++i)
    {
        result.setBitValue(result.m_length - i - 1, bitValue(m_length - i - 1) || other.bitValue(other.m_length - i - 1));
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
    int minLength = std::min(m_length, other.m_length);
    BoolVector result(*this);
    if (other.m_length > m_length)
    {
        result = other;
    }
    for (int i = 0; i < minLength; ++i)
    {
        result.setBitValue(result.m_length - i - 1, bitValue(m_length - i - 1) ^ other.bitValue(other.m_length - i - 1));
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

    if (position < 0)
    {
        std::cerr << "BoolVector::operator<<: negative shift value, will be inverted...\n";
        position = -position;
    }

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

    if (position < 0)
    {
        std::cerr << "BoolVector::operator>>: negative shift value, will be inverted...\n";
        position = -position;
    }

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



void BoolVector::Rank::swap(Rank &other) noexcept
{
    std::swap(m_cell, other.m_cell);
    std::swap(m_mask, other.m_mask);
}

std::istream& operator>>(std::istream &in, BoolVector &bv)
{
    bool value;
    for (int i = 0; i < bv.m_length; ++i)
    {
        in >> value;
        bv.setBitValue(i, value);
    }

    return in;
}

std::ostream &operator<<(std::ostream &out, const BoolVector &bv)
{
    if (bv.m_length == 0)
    {
        out << "boolean vector is empty\n";
    }
    else
    {
        out << '[';
        for (int i = 0; i < bv.m_length - 1; ++i)
        {
            out << bv.bitValue(i) << ", ";
        }
        out << bv.bitValue(bv.m_length - 1) << "]\n";
    }
    return out;
}
