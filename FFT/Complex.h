#ifndef COMPLEX_H
#define COMPLEX_H

#include "Arithmetical.h"

class Complex : public Arithmetical<Complex> {
    private: 
        double real;
        double imaginary;  
        std::string toString(double) const; 
        
    public:
        Complex(); 
        Complex(double, double);
        double getReal() const;
        double getImaginary() const;
        void setReal(double);
        void setImaginary(double);
        std::string toString() const;
        Complex complexConjugate() const; 
        Complex add(const Complex &r) const;
        Complex sub(const Complex &r) const;
        Complex mul(const Complex &r) const;
        Complex div(const Complex &r) const;
};

#endif
