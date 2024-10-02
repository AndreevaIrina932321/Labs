#pragma once
class Fraction
{
public:
    Fraction operator+(const Fraction & other) const;
    Fraction operator-(const Fraction & other) const;
    Fraction operator*(const Fraction & other) const;
    Fraction operator/(const Fraction & other) const;
    bool operator>(const Fraction & other);
    bool operator<(const Fraction & other);
    bool operator==(const Fraction & other);
    bool operator!=(const Fraction & other);
    void reduce();
    void print() const;
    int getIntegerPart();
    void printProperForm();
    int getNumerator() const;
    int getDenominator() const;
    void setNumerator(const int value);
    void setDenominator(const int value);
    Fraction() = default;
    Fraction(const int num, const int den);
    ~Fraction() = default;
private:
    int numerator = 1;
    int denominator = 1;
};
