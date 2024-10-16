#include <iostream>
#include <assert.h>
#include <algorithm>
#include "Array.h"

Array::Array(const int size, const int value)
{
    if (size < 0)
    {
        std::cerr << "Array::Array: size is negative, invert...\n";
        m_size = -size;
    }
    else m_size = size;

    m_array = new int[m_size];

    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = value;
    }
}

Array::Array(const int size, const int *arr)
{
    if (arr == nullptr)
    {
        std::cerr << "Array::Array: can't create Array from void array, Array will be default...\n";
        m_size = 10;
        m_array = new int[m_size];

        for (int i = 0; i < m_size; ++i)
        {
            m_array[i] = 0;
        }
    }
    else
    {
        m_size = size;
        m_array = new int[m_size];

        for (int i = 0; i < m_size; ++i)
        {
            m_array[i] = arr[i];
        }
    }
}

Array::Array(const Array &other)
    : m_size(other.m_size)
{
    m_array = new int[m_size];

    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = other.m_array[i];
    }
}

Array::Array(Array&& other)
    : m_size(other.m_size), m_array(other.m_array)
{
    other.m_array = nullptr;
}

Array::~Array()
{
    delete[] m_array;
}

int Array::getSize() const
{
    return m_size;
}

void Array::swap(Array& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

int Array::find(const int sample) const
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

void Array::print() const
{
    if (m_size == 0)
    {
        std::cout << "Array is empty\n";
    }
    else
    {
        std::cout << '[';
        for (int i = 0; i < m_size - 1; ++i)
        {
            std::cout << m_array[i] << ", ";
        }
        std::cout << m_array[m_size - 1] << "]\n";
    }
    std::cout << std::endl;
}

void Array::input()
{
    int sizeOfArray;
    std::cout << "Введите размер массива: ";
    std::cin >> sizeOfArray;
    if (sizeOfArray < 0)
    {
         std::cerr << "Array::Array: size is negative, invert...\n";
         sizeOfArray = -sizeOfArray;
    }
    m_size = sizeOfArray;
    std::cout << "Введите зеачения элементов массива: ";
    for (int i = 0; i < m_size; ++i)
    {
        std::cin >> m_array[i];
    }
}

void Array::sort()
{
    int temp, j;
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

bool Array::insert(const int index, const int &value)
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

bool Array::deleteIndex(const int index)
{
    //Array arrCopy(m_size - 1);
    int i;
    if (index >= m_size || index < 0)
    {
        std::cerr << "Array::deleteIndex: index is incorrect...\n";
        return false;
    }
    /*for (i = 0; i < index; i++)
    {
        arrCopy.m_array[i] = m_array[i];
    }
    for (; i < m_size; i++)
    {
        arrCopy.m_array[i] = m_array[i + 1];
    }
    swap(arrCopy);*/
    for (i = index; i < m_size; ++i)
    {
        m_array[i] = m_array[i + 1];
    }
    --m_size;
    return true;
}

bool Array::deleteFirst(const int &value)
{
    int index = find(value);
    if (index >= 0)
    {
        return deleteIndex(index);
    }
    return false;
}

Array &Array::erase(const int &value)
{
    bool inArray{true};
    do
    {
        inArray = deleteFirst(value);
    }
    while(inArray);
    return *this;
}

int Array::findMaxElement() const
{
    int maxValue = m_array[0];
    for (int i = 1; i < m_size; ++i)
    {
        if (maxValue < m_array[i])
            {
                maxValue = m_array[i];
            }
    }
    return maxValue;
}

int Array::findMinElement() const
{
    int minValue = m_array[0];
    for (int i = 1; i < m_size; ++i)
    {
        if (minValue > m_array[i])
            {
                minValue = m_array[i];
            }
    }
    return minValue;
}

Array &Array::operator=(const Array &other)
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

Array& Array::operator=(Array&& other) noexcept
{
    swap(other);
    return *this;
}

const int &Array::operator[](const int index) const
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

int &Array::operator[](const int index)
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

Array Array::operator+(const int &value) const
{
    Array sum(*this);
    sum.insert(m_size, value);
    return sum;
}

void Array::operator+=(const int &value)
{
    insert(m_size, value);
}

void Array::operator+=(const Array &other)
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
}

Array Array::operator+(const Array &other) const
{
    Array sum(*this);
    sum += (other);
    return sum;
}

bool Array::operator==(const Array &other) const
{
    if (m_size != other.m_size)
    {
        return true;
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

bool Array::operator!=(const Array &other) const
{
    return (!operator==(other));
}

Array::iterator Array::begin()
{
    return m_array;
}

Array::iterator Array::end()
{
    return m_array + m_size;
}

const Array::iterator Array::begin() const
{
    return m_array;
}

const Array::iterator Array::end() const
{
    return m_array + m_size;
}

Array &Array::erase(Array::iterator left, Array::iterator right, const int &value)
{
    iterator newEnd;
    if (left < begin() || right > end())
    {
        std::cerr << "Array::delete: borders is incorrect...\n";
        return *this;
    }
    newEnd = std::remove(left, right, value);
    m_size = newEnd - begin();
    return *this;
}

bool Array::insert(const Array::iterator position, const int &value)
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
