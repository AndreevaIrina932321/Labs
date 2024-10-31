#pragma once
#include <iostream>
#include <assert.h>
#include <algorithm>

template <typename ItemType>
class Array
{
public:
    typedef ItemType* iterator;
    typedef ItemType value_type;
    typedef ItemType& reference;
    typedef ItemType* pointer;
    typedef int difference_type;
public:

    Array(const int size = 10, const ItemType value = ItemType());
    Array(const int size, const ItemType *arr);
    Array(const Array &other);
    Array(Array&& other);
    ~Array();

    int getSize() const;
    void swap(Array &other) noexcept;
    int find(const ItemType sample) const;

    void sort();

    bool insert(const int index, const ItemType &value);

    bool deleteIndex(const int index);
    bool deleteFirst(const ItemType &value);
    Array &erase(const ItemType &value);

    ItemType max() const;
    ItemType min() const;

    Array &operator=(const Array &other);
    Array& operator=(Array&& other) noexcept;
    const ItemType &operator[](const int index) const;
    ItemType &operator[](const int index);

    Array operator+(const ItemType &value) const;
    Array operator+=(const ItemType &value);
    Array operator+(const Array &other) const;
    Array operator+=(const Array &other);

    bool operator==(const Array &other) const;
    bool operator!=(const Array &other) const;

    iterator begin();
    iterator end();
    const iterator begin() const;
    const iterator end() const;

    Array &erase(iterator left, iterator right, const ItemType &value);
    bool insert(const iterator position, const ItemType &value);

    template <typename T>
    friend std::ostream& operator<<(std::ostream &out, const Array<T> &arr);
    template <typename T>
    friend std::istream& operator>>(std::istream &in, Array<T> &arr);

private:
    ItemType *m_array = nullptr;
    int m_size = 0;
};

template <typename ItemType>
Array<ItemType>::Array(const int size, const ItemType value)
{
    if (size < 0)
    {
        std::cerr << "Array::Array: size is negative, invert...\n";
        m_size = -size;
    }
    else m_size = size;

    m_array = new ItemType[m_size];

    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = value;
    }
}

template <typename ItemType>
Array<ItemType>::Array(const int size, const ItemType *arr)
{
    if (arr == nullptr)
    {
        std::cerr << "Array::Array: can't create Array from void array, Array will be default...\n";
        m_size = 10;
        m_array = new ItemType[m_size];

        for (int i = 0; i < m_size; ++i)
        {
            m_array[i] = ItemType();
        }
    }
    else
    {
        m_size = size;
        m_array = new ItemType[m_size];

        for (int i = 0; i < m_size; ++i)
        {
            m_array[i] = arr[i];
        }
    }
}

template <typename ItemType>
Array<ItemType>::Array(const Array &other)
    : m_size(other.m_size)
{
    m_array = new ItemType[m_size];

    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = other.m_array[i];
    }
}

template <typename ItemType>
Array<ItemType>::Array(Array&& other)
    : m_size(other.m_size), m_array(other.m_array)
{
    other.m_array = nullptr;
}

template <typename ItemType>
Array<ItemType>::~Array()
{
    delete[] m_array;
}

template <typename ItemType>
int Array<ItemType>::getSize() const
{
    return m_size;
}

template <typename ItemType>
void Array<ItemType>::swap(Array& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

template <typename ItemType>
int Array<ItemType>::find(const ItemType sample) const
{
    for (int i = 0; i < m_size; ++i)
    {
        if (m_array[i] == sample)
            {
                return i;
            }
    }
    return -1;
}

template <typename ItemType>
void Array<ItemType>::sort()
{
    ItemType temp;
    int j;
    for (int i = 1; i < m_size; i++)
    {
        temp = m_array[i];
        for(j = i - 1; j >= 0 && m_array[j] > temp; j--)
        {
            m_array[j + 1] = m_array[j];
        }
        m_array[j + 1] = temp;
    }
}

template <typename ItemType>
bool Array<ItemType>::insert(const int index, const ItemType &value)
{
    Array arrCopy(m_size + 1);
    int i;
    if (index > m_size || index < 0)
    {
        std::cerr << "Array::insertElement: index is incorrect...\n";
        return false;
    }
    for (i = 0; i < index; i++)
    {
        arrCopy.m_array[i] = m_array[i];
    }
    arrCopy.m_array[i] = value;
    for (i = i + 1; i <= m_size; i++)
    {
        arrCopy.m_array[i] = m_array[i - 1];
    }
    swap(arrCopy);
    return true;
}

template <typename ItemType>
bool Array<ItemType>::deleteIndex(const int index)
{
    int i;
    Array arrCopy(m_size - 1);
    if (index >= m_size || index < 0)
    {
        std::cerr << "Array::deleteIndex: index is incorrect...\n";
        return false;
    }
    for (i = 0; i < index; ++i)
    {
        arrCopy[i] = m_array[i];
    }
    for (i = index; i < m_size; ++i)
    {
        m_array[i] = m_array[i + 1];
    }
    swap(arrCopy);
    return true;
}

template <typename ItemType>
bool Array<ItemType>::deleteFirst(const ItemType &value)
{
    int index = find(value);
    if (index >= 0)
    {
        return deleteIndex(index);
    }
    return false;
}

template <typename ItemType>
Array<ItemType> &Array<ItemType>::erase(const ItemType &value)
{
    bool inArray{true};
    do
    {
        inArray = deleteFirst(value);
    }
    while(inArray);
    return *this;
}

template <typename ItemType>
ItemType Array<ItemType>::max() const
{
    ItemType maxValue = m_array[0];
    for (int i = 1; i < m_size; ++i)
    {
        if (maxValue < m_array[i])
            {
                maxValue = m_array[i];
            }
    }
    return maxValue;
}

template <typename ItemType>
ItemType Array<ItemType>::min() const
{
    ItemType minValue = m_array[0];
    for (int i = 1; i < m_size; ++i)
    {
        if (minValue > m_array[i])
            {
                minValue = m_array[i];
            }
    }
    return minValue;
}

template <typename ItemType>
Array<ItemType> &Array<ItemType>::operator=(const Array &other)
{
    if (this == &other)
    {
        return *this;
    }

    if (m_size == other.m_size)
    {
        for (int i = 0; i < m_size; ++i)
        {
            m_array[i] = other.m_array[i];
        }
    }
    else
    {
        Array arrCopy(other);
        swap(arrCopy);
    }
    return *this;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(Array&& other) noexcept
{
    swap(other);
    return *this;
}

template <typename ItemType>
const ItemType &Array<ItemType>::operator[](const int index) const
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename ItemType>
ItemType &Array<ItemType>::operator[](const int index)
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const ItemType &value) const
{
    Array sum(*this);
    sum.insert(m_size, value);
    return sum;
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+=(const ItemType &value)
{
    insert(m_size, value);
    return *this;
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+=(const Array &other)
{
    Array sum(m_size + other.m_size);
    int i;
    for (i = 0; i < m_size; ++i)
    {
        sum.m_array[i] = m_array[i];
    }
    i = 0;
    for (int j = m_size; j < sum.m_size; ++j, ++i)
    {
        sum.m_array[j] = other.m_array[i];
    }
    swap(sum);
    return *this;
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const Array &other) const
{
    Array sum(*this);
    sum += (other);
    return sum;
}

template <typename ItemType>
bool Array<ItemType>::operator==(const Array &other) const
{
    if (m_size != other.m_size)
    {
        return false;
    }
    for (int i = 0; i < m_size; ++i)
    {
        if (m_array[i] != other.m_array[i])
            {
                return false;
            }
    }
    return true;
}

template <typename ItemType>
bool Array<ItemType>::operator!=(const Array &other) const
{
    return (!operator==(other));
}

template <typename ItemType> typename
Array<ItemType>::iterator Array<ItemType>::begin()
{
    return m_array;
}

template <typename ItemType> typename
Array<ItemType>::iterator Array<ItemType>::end()
{
    return m_array + m_size;
}

template <typename ItemType>
const typename Array<ItemType>::iterator Array<ItemType>::begin() const
{
    return m_array;
}

template <typename ItemType>
const typename Array<ItemType>::iterator Array<ItemType>::end() const
{
    return m_array + m_size;
}

template <typename ItemType>
Array<ItemType> &Array<ItemType>::erase(Array<ItemType>::iterator left, Array<ItemType>::iterator right, const ItemType &value)
{
    iterator newEnd, copyIndex;
    if (left < begin() || right > end())
    {
        std::cerr << "Array::delete: borders is incorrect...\n";
        return *this;
    }
    newEnd = std::remove(left, right, value);
    Array arrCopy(newEnd - begin());
    int i = 0;
    for (copyIndex = arrCopy.begin(); copyIndex < arrCopy.end(); ++copyIndex, ++i)
    {
        *copyIndex = *(begin() + i);
    }
    swap(arrCopy);
    return *this;
}

template <typename ItemType>
bool Array<ItemType>::insert(const Array<ItemType>::iterator position, const ItemType &value)
{
    if (position < begin() || position >= end())
    {
        std::cerr << "Array::insert: iterator is incorrect...\n";
        false;
    }
    Array copyArr(m_size + 1);
    iterator it, otherIt = copyArr.begin();
    for (it = begin(); it < position; ++it, ++otherIt)
    {
        *otherIt = *it;
    }
    *otherIt = value;
    ++otherIt;
    while (it != end())
    {
        *otherIt = *it;
    }
    swap(copyArr);
    return true;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Array<T> &arr)
{
    if (arr.m_size == 0)
    {
        out << "Array is empty\n";
    }
    else
    {
        out << '[';
        for (int i = 0; i < arr.m_size - 1; ++i)
        {
            out << arr.m_array[i] << ", ";
        }
        out << arr.m_array[arr.m_size - 1] << "]\n";
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream &in, Array<T> &arr)
{
    if (arr.m_size < 0)
    {
         std::cerr << "Array::Array: size is negative, invert...\n";
         arr.m_size = -arr.m_size;
    }
    for (int i = 0; i <arr.m_size; ++i)
    {
        in >> arr.m_array[i];
    }
    return in;
}
