#pragma once

#include <iostream>

// TODO: task 7.2 a)
class ComplexNumber
{
public:
    ComplexNumber() noexcept = default;
    ComplexNumber(double real, double imaginary = 0.0) : real_number(real), imaginary_number(imaginary) {};

    ComplexNumber& operator+=(const ComplexNumber& rhs);

    friend std::ostream& operator<<(std::ostream&, const ComplexNumber&);

    double getIm() const { return imaginary_number; };
    double getRe() const { return real_number; }

private:
    double real_number{};
    double imaginary_number{};
};

// TODO: task 7.2 b) - unary operator+= (class member, modifying)
ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other)
{
    // TODO
}

// TODO: task 7.2 b) - binary operator+ (free function, non-modifying: returns new complex number)
ComplexNumber operator +(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
    // TODO
    return {};
}

std::ostream& operator<<(std::ostream& out, const ComplexNumber& complex)
{
    // TODO
}
