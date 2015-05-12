#include "Rational.h"
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

Rational::Rational() {
    nom = 0;
    den = 1;
}

Rational::Rational(long n) {
    nom = n;
    den = 1;
}

Rational::Rational(long n, long d) {
    nom = n;
    den = d;
    assert(den != 0);
    simplify();
}

string Rational::toString() const { 
    if (nom == 0) return "0";
    if (den == 1) return toString(nom);
    else          return toString(nom) + "/" + toString(den);
}

long Rational::getNom() const {
    return nom;
}

long Rational::getDen() const {
    return den;
}

void Rational::setNom(long n) {
    nom = n;
}

void Rational::setDen(long d) {
    den = d;
}

Rational Rational::add(const Rational &r) const {
    long LCM = lcm(den, r.den);
    long thisNom = nom * (LCM / den);
    long thatNom = r.nom * (LCM / r.den);
    return Rational(thisNom + thatNom, LCM);
}

Rational Rational::sub(const Rational &r) const {
    return add(r.mul(Rational(-1)));
}

Rational Rational::mul(const Rational &r) const {
    return Rational(nom * r.nom, den * r.den);
}

Rational Rational::div(const Rational &r) const {
    return mul(r.reciprocal());
}

Rational Rational::reciprocal() const {
    return Rational(den, nom);
}

double Rational::doubleValue() const {
    return double(nom)/double(den);
}

int Rational::compareTo(const Rational &r) const {
    if (nom == r.nom && den == r.den)    return  0;
    if (doubleValue() > r.doubleValue()) return  1;
    else                                 return -1;
} 

void Rational::simplify() {
    long GCD = gcd(nom, den);
    nom /= GCD;
    den /= GCD;
    if (den < 0) {
        nom *= -1;
        den *= -1;
    }
}

long Rational::gcd(long a, long b) const {
    if(a % b == 0) return b;
    return gcd(b, a % b);
}

long Rational::lcm(long a, long b) const {
    if (abs(a) == abs(b)) 
        return abs(a);
    return abs(a * b) / gcd(a, b);
} 

string Rational::toString(long n) const {
    stringstream s;
    s << n;
    return s.str();
}

Rational::operator double() {
    return doubleValue();
}

