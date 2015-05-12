#include "Complex.h"
#include <iostream> 
#include <sstream>
using namespace std;

Complex::Complex() {
    real = 0;
    imaginary = 0;
} 

Complex::Complex(double r, double i) {
    real = r;
    imaginary = i;
}

string Complex::toString() const {
    string c = (real != 0 ? toString(real) : "") + (imaginary != 0 ? ((imaginary >= 0 ? "+" : "") + toString(imaginary) + "i") : "");
    return (c.length() != 0 ? c : "0");
}

double Complex::getReal() const {
    return real;
}

double Complex::getImaginary() const {
    return imaginary;
}

void Complex::setReal(double r) {
    real = r;
}

void Complex::setImaginary(double i) {
    imaginary = i;
}

Complex Complex::complexConjugate() const {
    return Complex(real, -imaginary);
}

Complex Complex::add(const Complex &c) const {
    return Complex(real + c.real, imaginary + c.imaginary);
}

Complex Complex::sub(const Complex &c) const { 
    return Complex(real - c.real, imaginary - c.imaginary);
}

Complex Complex::mul(const Complex &c) const { //foil
    return Complex((real * c.real) - (imaginary * c.imaginary) , (real * c.imaginary) + (imaginary * c.real));
}

Complex Complex::div(const Complex &c) const { 
    Complex cj  = c.complexConjugate();
    Complex nom = mul(cj);
    Complex den = c.mul(cj);
    return nom.mul(Complex(1/den.getReal(), 0));
}

string Complex::toString(double d) const {
    stringstream s;
    s << d;
    return s.str();
}
