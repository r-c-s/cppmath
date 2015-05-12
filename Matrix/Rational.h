#ifndef RATIONAL_H
#define RATIONAL_H

#include "Arithmetical.h"
#include "Comparable.h" 

class Rational : public Arithmetical<Rational>, public Comparable<Rational> { 
    private:
        long nom;
        long den;  
        void simplify();
        long gcd(long, long) const;
        long lcm(long, long) const; 
        std::string toString(long) const; 
        
    public:
        Rational();
        Rational(long);
        Rational(long, long);
        long getNom() const;
        long getDen() const;
        void setNom(long);
        void setDen(long);
        std::string toString() const;
        Rational reciprocal() const;
        double doubleValue() const;
        Rational add(const Rational &r) const;
        Rational sub(const Rational &r) const;
        Rational mul(const Rational &r) const;
        Rational div(const Rational &r) const;
        int compareTo(const Rational &r) const; 
        operator double(); 
};

#endif
