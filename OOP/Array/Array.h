#pragma once
class Array
{
public:
    Array(const int size = 10, const int value = 0);
    Array(const int size, const int *arr);
    Array(const Array &other);
    Array(Array&& other);
    ~Array();

    int getSize() const;
    void swap(Array &other) noexcept;
    int findElement(const int sample) const;
    void print() const;
    void insertSort();

    bool insertElement(const int index, const int &value);

    bool deleteIndex(const int index);
    bool deleteFirst(const int &value);
    Array &deleteAll(const int &value);

    int findMaxElement();

    Array &operator=(const Array &other);
    Array& operator=(Array&& other) noexcept;
    const int &operator[](const int index) const;
    int &operator[](const int index);

    Array operator+(const int &value) const;
    void operator+=(const int &value);
    Array operator+(const Array &other) const;
    void operator+=(const Array &other);

    bool operator==(const Array &other);
    bool operator!=(const Array &other);

private:
    int *m_array = nullptr;
    int m_size = 0;
};

