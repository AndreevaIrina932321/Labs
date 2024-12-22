#include <assert.h>
#include <iostream>
#include "Set.h"
#include "/home/rin/Labs/OOP/BoolVector/BoolVector.cpp"

Set::Set(const char *sample, const int sampleSize)
    :BoolVector(maxSize, false)
{
    assert(sampleSize >= 0 && sample != nullptr);
    for (int i = 0; i < sampleSize; ++i)
    {
        setBitValue(static_cast<Cell>(sample[i]), true);
    }
}

Set::Set(const Set &other)
    :BoolVector(other)
{}

Set::Set(const BoolVector &bv)
    :BoolVector(bv)
{}

Set::~Set()
{
    ~BoolVector();
}

bool Set::inSet(const char value) const
{
    return bitValue(static_cast<Cell>(value));
}

char Set::min() const
{
    int i;
    for (i = 0; !bitValue(i); ++i) {}
    return static_cast<Cell>(i);
}

char Set::max() const
{
    int i;
    for (i = maxSize - 1; !bitValue(i); --i) {}
    return static_cast<Cell>(i);
}

int Set::size() const
{
    return getWeight();
}

Set &Set::operator=(const Set &other)
{
    BoolVector::operator=(other);
    return *this;
}

bool Set::operator==(const Set &other) const
{
    int i;
    for (i = 0; i < maxSize && bitValue(i) == other.bitValue(i); ++i) {}
    return i == maxSize;
}

bool Set::operator!=(const Set &other) const
{
    return !operator==(other);
}

Set Set::operator&(const Set &other) const
{
    return BoolVector::operator&(other);
}

Set &Set::operator&=(const Set &other)
{
    BoolVector::operator&=(other);
    return *this;
}

Set Set::operator|(const Set &other) const
{
    return BoolVector::operator|(other);
}

Set &Set::operator|=(const Set &other)
{
    BoolVector::operator|=(other);
    return *this;
}

Set Set::operator/(const Set &other) const
{
    Set result(*this);
    result &= other;
    ~result;
    return result &= *this;
}

Set &Set::operator/=(const Set &other)
{
    operator/(other).swap(*this);
    return *this;
}

Set Set::operator~() const
{
    BoolVector::operator~();
    return *this;
}

Set &Set::operator+=(const char value)
{
    operator+(value).swap(*this);
    return *this;
}

Set Set::operator+(const char value) const
{
    Set result(*this);
    if (!result.inSet(value))
    {
        result.setBitValue(static_cast<unsigned int>(value), true);
    }
    return result;
}

Set &Set::operator-=(const char value)
{
    operator-(value).swap(*this);
    return *this;
}

Set Set::operator-(const char value) const
{
    Set result(*this);
    if (result.inSet(value))
    {
        result.setBitValue(static_cast<unsigned int>(value), false);
    }
    else
    {
        std::cerr << "Set::operator-: incorrect value, no changes...\n";
    }
    return result;
}

std::ostream& operator<<(std::ostream &out, const Set &set)
{
    out << '[';
    for (int i = 0; i < set.maxSize; ++i)
    {
        if (set.bitValue(i))
        {
            unsigned char a(i);
            out << "'" << a << "' ";
        }
    }
    out << "]\n";
    return out;
}

std::istream& operator>>(std::istream &in, Set &set)
{
    char a;
    int i = 0;
    while (i < set.size())
    {
        in >> a;
        set.BoolVector::setBitValue(static_cast<unsigned char>(a), true);
        ++i;
    }
    return in;
}

