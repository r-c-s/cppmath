#include "Arithmetical.h"
#include "Comparable.h"
#ifndef BIGINT_H
#define BIGINT_H

class BigInt : public Arithmetical<BigInt>, public Comparable<BigInt> {
        std::string value; 
        bool positive; 

    public:
        BigInt();
        BigInt(std::string);	
        std::string toString() const;	
        BigInt add(const BigInt &b) const;	 
        BigInt sub(const BigInt &b) const;	 
        BigInt mul(const BigInt &b) const; 
        BigInt div(const BigInt &b) const;	
        BigInt abs() const; 
        BigInt fact() const;	 
        BigInt pow(int) const; 	  	
        BigInt mod(const BigInt &b) const; 
        int compareTo(const BigInt &b) const; 
        
    private:  	
        BigInt pow2(int) const;
        void setValue(std::string);
        bool isANum(std::string) const;
        bool lessThan(const BigInt &b) const;
        std::string trim(std::string) const;
        std::string parseArray(int*, const int) const;
        std::string toString(int) const;
        unsigned long toLong(std::string) const;
        int toInt(std::string) const;
        int toInt(char) const;
};

#endif
