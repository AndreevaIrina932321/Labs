#pragma once
class Fraction
{
public:
    Fraction() = default;
    Fraction(const int num, const int den);
    ~Fraction() = default;
    int getNumerator() const;
    int getDenominator() const;
    void setNumerator(const int value);
    void setDenominator(const int value);
    void reduce();
    void print() const;
    int getIntegerPart() const;
    void printProperForm() const;
    bool operator>(const Fraction & other) const;
    bool operator<(const Fraction & other) const;
    bool operator==(const Fraction & other) const;
    bool operator!=(const Fraction & other) const;
    Fraction operator+(const Fraction & other) const;
    Fraction operator-(const Fraction & other) const;
    Fraction operator*(const Fraction & other) const;
    Fraction operator/(const Fraction & other) const;

private:
    int numerator;
    int denominator;
};
