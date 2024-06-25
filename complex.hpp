#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double real = 0.0, double imag = 0.0);

    double getReal() const;
    double getImag() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    bool operator>(const Complex& other) const;
    bool operator<(const Complex& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#endif // COMPLEX_HPP
