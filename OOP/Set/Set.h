#pragma once

#include "/home/rin/Labs/OOP/BoolVector/BoolVector.h"

class Set : public BoolVector
{
public:
    static const int maxSize = 256;

    Set(const char *sample, const int sampleSize);
    Set(const Set &other);
    Set(const BoolVector &bv);
    ~Set();

    bool inSet(const char value) const;
    char min() const;
    char max() const;
    int size() const;

    Set &operator=(const Set &other);
    bool operator==(const Set &other) const;
    bool operator!=(const Set &other) const;
	Set operator&(const Set &other) const;
	Set &operator&=(const Set &other);
	Set operator|(const Set &other) const;
	Set &operator|=(const Set &other);
	Set operator/(const Set &other) const;
	Set &operator/=(const Set &other);
	Set operator~() const;
	Set &operator+=(const char value);
	Set operator+(const char value) const;
	Set &operator-=(const char value);
	Set operator-(const char value) const;

	friend std::ostream& operator<<(std::ostream &out, const Set &set);
    friend std::istream& operator>>(std::istream &in, Set &set);

};
