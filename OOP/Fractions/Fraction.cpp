#include <iostream>
#include "Fraction.h"

Fraction Fraction::operator+(const Fraction &other) const
{
    Fraction sumOfFractions;
    sumOfFractions.numerator = numerator * other.denominator + other.numerator * denominator;
    sumOfFractions.denominator = other.denominator * denominator;
    return sumOfFractions;
}

Fraction Fraction::operator-(const Fraction &other) const
{
    Fraction subOfFractions;
    subOfFractions.numerator = numerator * other.denominator - other.numerator * denominator;
    subOfFractions.denominator = other.denominator * denominator;
    return subOfFractions;
}

Fraction Fraction::operator*(const Fraction &other) const
{
    Fraction mulOfFractions;
    mulOfFractions.numerator = numerator * other.numerator;
    mulOfFractions.denominator = other.denominator * denominator;
    return mulOfFractions;
}

Fraction Fraction::operator/(const Fraction &other) const
{
    if (other.numerator == 0)
    {
        std::cerr << "Fraction::div: error: a.numerator is 0, result will be 0/1.";
        return Fraction(0, 1);
    }
    Fraction divOfFractions;
    divOfFractions.numerator = numerator * other.denominator;
    divOfFractions.denominator = other.numerator * denominator;
    return divOfFractions;
}

bool Fraction::operator>(const Fraction &other) const
{
    return (numerator * other.denominator > denominator * other.numerator);
}

bool Fraction::operator<(const Fraction &other) const
{
    return (numerator * other.denominator < denominator * other.numerator);
}

bool Fraction::operator==(const Fraction &other) const
{
    return (numerator * other.denominator == denominator * other.numerator);
}

bool Fraction::operator!=(const Fraction &other) const
{
    return (!operator==(other));
}

void Fraction::reduce()
{
    int nod, a = denominator, b = numerator;
    while (a != 0 && b != 0)
    {
        if (a > b) a %= b;
        else b %= a;
    }
    nod = a + b;
    denominator /= nod;
    numerator /= nod;
}

int Fraction::getIntegerPart() const
{
    int integer;
    if (denominator == 1)
        integer = numerator;
    else integer = numerator / denominator;
    return integer;
}

void Fraction::printProperForm() const
{
    if (denominator == 1)
        std::cout << numerator;
    else if (numerator > denominator) std::cout << numerator / denominator << '+'
                << '(' << numerator % denominator << '/' << denominator << ')' << std::endl;
    else print();
}

void Fraction::print() const
{
    std::cout << numerator << '/' << denominator << std::endl;
}

int Fraction::getNumerator() const
{
    return numerator;
}

int Fraction::getDenominator() const
{
    return denominator;
}

void Fraction::setNumerator(const int value)
{
    numerator = value;
}

void Fraction::setDenominator(const int value)
{
    if (value == 0)
    {
        std::cerr << "Fraction::setDenominator: error: value is 0, won't assign, result will be numerator/1.\n";
        denominator = 1;
        return;
    }

    denominator = value;
}

Fraction::Fraction(const int num, const int den)
{
    numerator = num;
    if (den == 0)
    {
        std::cerr << "Fraction::Fraction: error: denominator is 0, result will be numerator/1.\n";
    }
    else
    {
        denominator = den;
    }

    if (denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }
}
