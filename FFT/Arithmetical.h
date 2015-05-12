#ifndef ARITHMETICAL_H
#define ARITHMETICAL_H

#include <sstream>

template <typename T> class Arithmetical {
    public:
        virtual std::string toString() const = 0;
        
        virtual T add(const T &n) const = 0;
        virtual T sub(const T &n) const = 0;
        virtual T mul(const T &n) const = 0;
        virtual T div(const T &n) const = 0;
        
        T operator+(const T &n) const { return add(n); }
        T operator-(const T &n) const { return sub(n); }
        T operator*(const T &n) const { return mul(n); }
        T operator/(const T &n) const { return div(n); }
};

template <typename T> std::ostream &operator<<(std::ostream &out, const Arithmetical<T> &n) { 
    out << n.toString();
    return out;
}

#endif
