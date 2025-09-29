/*
Philipp Schmid: 5703070
Max Staneker: 7018590
*/
#pragma once

#include <iostream>

// TODO: task 7.2 a)
template<typename T>
class ComplexNumber
{
public:
    ComplexNumber() noexcept = default;
    ComplexNumber(T real, T imaginary = T{}) : real_number(real), imaginary_number(imaginary) {};

    ComplexNumber& operator+=(const ComplexNumber& rhs);

    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const ComplexNumber<U>&);

    T getIm() const { return imaginary_number; };
    T getRe() const { return real_number; }

private:
    T real_number{};
    T imaginary_number{};
};

// TODO: task 7.2 b) - unary operator+= (class member, modifying)
template<typename T>
ComplexNumber<T>& ComplexNumber<T>::operator+=(const ComplexNumber<T>& other)
{
    // TODO
    real_number += other.real_number;
    imaginary_number += other.imaginary_number;
    return *this;
}

// TODO: task 7.2 b) - binary operator+ (free function, non-modifying: returns new complex number)
template<typename T>
ComplexNumber<T> operator +(ComplexNumber<T> lhs, const ComplexNumber<T>& rhs)
{
    // TODO
    lhs += rhs;
    return lhs;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const ComplexNumber<T>& complex)
{
    // TODO
    //real part
    out << complex.getRe();
    //imaginary part
    T imaginary = complex.getIm();
    if (imaginary >= T{}) {
        out << '+' << imaginary << 'i';}
    else {
        out << imaginary << 'i';
    }
    return out;
}
