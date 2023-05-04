#pragma once

#include <iostream>

namespace ariel
{
    class Fraction
    {
        int numerator;
        int denominator;

        void reduce();
        float toFloat();

    public:
        Fraction(int num, int den);
        Fraction(float flt);
        Fraction();
        //copy constructor
        Fraction(const Fraction &frac);
        //copy assignment operator
        Fraction& operator=(const Fraction &other);
        //move constructor
        Fraction(Fraction&& other) noexcept;
        //move assignment operator
        Fraction& operator=(Fraction&& other) noexcept;
        ~Fraction();

        int getNumerator();
        int getDenominator();

        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;
        friend Fraction operator+(const Fraction &other, float flt);
        friend Fraction operator-(const Fraction &other, float flt);
        friend Fraction operator*(const Fraction &other, float flt);
        friend Fraction operator/(const Fraction &other, float flt);
        friend Fraction operator+(float flt, const Fraction &other);
        friend Fraction operator-(float flt, const Fraction &other);
        friend Fraction operator*(float flt, const Fraction &other);
        friend Fraction operator/(float flt, const Fraction &other);

        // comparison operators
        bool operator==(const Fraction &other) const;
        bool operator!=(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        friend bool operator==(const Fraction &other, float flt);
        friend bool operator!=(const Fraction &other, float flt);
        friend bool operator>(const Fraction &other, float flt);
        friend bool operator<(const Fraction &other, float flt);
        friend bool operator>=(const Fraction &other, float flt);
        friend bool operator<=(const Fraction &other, float flt);
        friend bool operator==(float flt, const Fraction &other);
        friend bool operator!=(float flt, const Fraction &other);
        friend bool operator>(float flt, const Fraction &other);
        friend bool operator<(float flt, const Fraction &other);
        friend bool operator>=(float flt, const Fraction &other);
        friend bool operator<=(float flt, const Fraction &other);

        // increment and decrement operators
        Fraction &operator++();   // prefix
        Fraction operator++(int); // postfix
        Fraction &operator--();   // prefix
        Fraction operator--(int); // postfix

        // stream insertion and extraction operators
        friend std::ostream &operator<<(std::ostream &output, const Fraction &fraction);
        friend std::istream &operator>>(std::istream &input, Fraction &fraction);
    };





}