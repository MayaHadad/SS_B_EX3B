#include <iostream>
#include <limits.h>
#include "Fraction.hpp"

using namespace std;

int gcd(int num1, int num2)
{
    if (num2 == 0)
        return num1;
    return gcd(num2, num1 % num2);
}

int checkOverflow(int num1, int num2, char opr)
{
    int result;
    switch (opr)
    {
    case '+':
        if ((num1 >= 0 && num2 > INT_MAX - num1) || (num1 < 0 && num2 < INT_MIN - num1))
            result = 1;
        else
            result = 0;
        break;
    case '-':
        if ((num1 >= 0 && num2 < INT_MIN + num1) || (num1 < 0 && num2 > INT_MAX + num1 +1)) 
            result = 1;
        else
            result = 0;
        break;
    case '*':
        if ((num1 > 0 && num2 > 0 && num1 > INT_MAX / num2) || (num1 > 0 && num2 < 0 && num2 < INT_MIN / num1) ||
                (num1 < 0 && num2 > 0 && num1 < INT_MIN / num2) || (num1 < 0 && num2 < 0 && num1 < INT_MAX / num2)) 
            result = 1;
        else
            result = 0;
    default:
        break;
    }
    return result;
}

namespace ariel
{
    Fraction::Fraction(int num, int den)
        : numerator(num), denominator(den)
    {
        if (den == 0)
            throw invalid_argument("Invalid syntax");
        this->reduce();
    }

    Fraction::Fraction(const Fraction &frac)
    {
        this->numerator = frac.numerator;
        this->denominator = frac.denominator;
    }

    Fraction::Fraction(float flt)
    {
        float temp = flt * 1000;
        this->numerator = (int)temp;
        this->denominator = 1000;
        this->reduce();
    }

    Fraction::Fraction()
    {
        this->numerator = 0;
        this->denominator = 1;
    }

    Fraction &Fraction::operator=(const Fraction &other)
    {
        if (this != &other)
        {
            this->numerator = other.numerator;
            this->denominator = other.denominator;
        }
        return *this;
    }

    Fraction::Fraction(Fraction &&other) noexcept : numerator(move(other.numerator)), denominator(move(other.denominator))
    {
    }

    Fraction &Fraction::operator=(Fraction &&other) noexcept
    {
        if (this != &other)
        {
            numerator = move(other.numerator);
            denominator = move(other.denominator);
        }
        return *this;
    }

    Fraction::~Fraction()
    {
    }

    void Fraction::reduce()
    {
        int fracgcd = gcd(this->numerator, this->denominator);
        this->numerator /= fracgcd;
        this->denominator /= fracgcd;
        if (this->denominator < 0 && this->numerator >= 0)
        {
            this->denominator *= (-1);
            this->numerator *= (-1);
        }
    }

    int Fraction::getNumerator()
    {
        return this->numerator;
    }
    int Fraction::getDenominator()
    {
        return this->denominator;
    }

    Fraction Fraction::operator+(const Fraction &other) const
    {
        int num = checkOverflow((this->numerator * other.denominator), (this->denominator * other.numerator), '+');
        int den = checkOverflow(this->denominator, other.denominator, '*');
        if (num == 1 || den == 1)
            throw overflow_error("stack overflow");
        num = (this->numerator * other.denominator) + (this->denominator * other.numerator);
        den = this->denominator * other.denominator;
        return Fraction(num, den);
    }
    Fraction Fraction::operator-(const Fraction &other) const
    {
        int num = checkOverflow((this->numerator * other.denominator), (this->denominator * other.numerator), '-');
        int den = checkOverflow(this->denominator, other.denominator, '*');
        if (num == 1 || den == 1)
            throw overflow_error("stack overflow -");
        num = (this->numerator * other.denominator) - (this->denominator * other.numerator);
        den = this->denominator * other.denominator;
        return Fraction(num, den);
    }
    Fraction Fraction::operator*(const Fraction &other) const
    {
        int num = checkOverflow(other.numerator, this->numerator, '*');
        int den = checkOverflow(other.denominator, this->denominator, '*');
        if (num == 1 || den == 1)
            throw overflow_error("stack overflow");
        num = other.numerator * this->numerator;
        den = other.denominator * this->denominator;
        return Fraction(num, den);
    }
    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.numerator == 0)
            throw runtime_error("can't devide by zero");
        int num = checkOverflow(this->numerator, other.denominator, '*');
        int den = checkOverflow(this->denominator, other.numerator, '*');
        if (num == 1 || den == 1)
            throw overflow_error("stack overflow");
        num = this->numerator * other.denominator;
        den = this->denominator * other.numerator;
        return Fraction(num, den);
    }

    Fraction operator+(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return other + frac;
    }
    Fraction operator-(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return other - frac;
    }
    Fraction operator*(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return other * frac;
    }
    Fraction operator/(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return other / frac;
    }
    Fraction operator+(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return frac + other;
    }
    Fraction operator-(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return frac - other;
    }
    Fraction operator*(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return frac * other;
    }
    Fraction operator/(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return frac / other;
    }

    // comparison operators
    bool Fraction::operator==(const Fraction &other) const
    {
        if (this->denominator == other.denominator && this->numerator == other.numerator)
            return true;
        return false;
    }
    bool Fraction::operator!=(const Fraction &other) const
    {
        if (this->denominator != other.denominator || this->numerator != other.numerator)
            return true;
        return false;
    }
    bool Fraction::operator>(const Fraction &other) const
    {
        int thisnum = this->numerator * other.denominator;
        int othernum = this->denominator * other.numerator;
        if (thisnum > othernum)
            return true;
        return false;
    }
    bool Fraction::operator<(const Fraction &other) const
    {
        int thisnum = this->numerator * other.denominator;
        int othernum = this->denominator * other.numerator;
        if (thisnum < othernum)
            return true;
        return false;
    }
    bool Fraction::operator>=(const Fraction &other) const
    {
        int thisnum = this->numerator * other.denominator;
        int othernum = this->denominator * other.numerator;
        if (thisnum >= othernum)
            return true;
        return false;
    }
    bool Fraction::operator<=(const Fraction &other) const
    {
        int thisnum = this->numerator * other.denominator;
        int othernum = this->denominator * other.numerator;
        if (thisnum <= othernum)
            return true;
        return false;
    }
    bool operator==(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return other == frac;
    }
    bool operator!=(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return other != frac;
    }
    bool operator>(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return (other > frac);
    }
    bool operator<(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return (other < frac);
    }
    bool operator>=(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return (other >= frac);
    }
    bool operator<=(const Fraction &other, float flt)
    {
        Fraction frac(flt);
        return other <= frac;
    }
    bool operator==(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return frac == other;
    }
    bool operator!=(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return frac != other;
    }
    bool operator>(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return (frac > other);
    }
    bool operator<(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return (frac < other);
    }
    bool operator>=(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return (frac >= other);
    }
    bool operator<=(float flt, const Fraction &other)
    {
        Fraction frac(flt);
        return (frac <= other);
    }

    // increment and decrement operators
    Fraction &Fraction::operator++()
    {
        this->numerator += this->denominator;
        return *this;
    }
    Fraction Fraction::operator++(int)
    {
        Fraction frac(*this);
        ++(*this);
        return frac;
    }
    Fraction &Fraction::operator--()
    {
        this->numerator -= this->denominator;
        return *this;
    }
    Fraction Fraction::operator--(int)
    {
        Fraction frac(*this);
        --(*this);
        return frac;
    }

    ostream &operator<<(ostream &output, const Fraction &frac)
    {
        output << frac.numerator << '/' << frac.denominator;
        return output;
    }
    istream &operator>>(istream &input, Fraction &frac)
    {
        int num, den;
        char slash;

        input >> num;
        if (input.fail())
            throw runtime_error("Invalid syntax");
        if (input.peek() == '/')
        {
            input >> slash >> den;
            if (input.fail() || den == 0)
                throw runtime_error("Invalid syntax");
        }
        else
        {
            input >> den;
            if (input.fail() || den == 0)
                throw runtime_error("Invalid syntax");
        }

        frac = Fraction(num, den);

        return input;
    }
}