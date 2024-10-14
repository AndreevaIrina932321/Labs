#pragma once
class Array
{
public:
    typedef int* iterator;
    typedef int value_type;
    typedef int& reference;
    typedef int* pointer;
    typedef int difference_type;
public:

    Array(const int size = 10, const int value = 0);
    Array(const int size, const int *arr);
    Array(const Array &other);
    Array(Array&& other);
    ~Array();

    int getSize() const;
    void swap(Array &other) noexcept;
    int find(const int sample) const;
    void print() const;
    void input();
    void sort();

    bool insert(const int index, const int &value);

    bool deleteIndex(const int index);
    bool deleteFirst(const int &value);
    Array &erase(const int &value);

    int findMaxElement() const;
    int findMinElement() const;

    Array &operator=(const Array &other);
    Array& operator=(Array&& other) noexcept;
    const int &operator[](const int index) const;
    int &operator[](const int index);

    Array operator+(const int &value) const;
    void operator+=(const int &value);
    Array operator+(const Array &other) const;
    void operator+=(const Array &other);

    bool operator==(const Array &other) const;
    bool operator!=(const Array &other) const;

    iterator begin();
    iterator end();
    const iterator begin() const;
    const iterator end() const;

    Array &erase(iterator left, iterator right, const int &value);
    bool insert(const iterator position, const int &value);

private:
    int *m_array = nullptr;
    int m_size = 0;
};

