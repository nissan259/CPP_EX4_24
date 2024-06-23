#include "complex.hpp"
#include <stdexcept>
#include <iomanip> // Include this for std::fixed and std::setprecision

Complex::Complex(double real, double imag) : real(real), imag(imag) {}

double Complex::getReal() const {
    return real;
}

double Complex::getImag() const {
    return imag;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return Complex((real * other.real + imag * other.imag) / denominator,
                   (imag * other.real - real * other.imag) / denominator);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << std::fixed << std::setprecision(2); // Set precision to 2 decimal places
    os << "(" << c.real << " + " << c.imag << "i)";
    return os;
}