#include "../bigint/BigInt.cpp"
#ifndef PERMUTATION_H
#define PERMUTATION_H

template <class T> class Permutation {
        T* items;
        T* firstPerm;
        T* lastPerm; 
        T size;  
    
    public:
        Permutation(T*, T);  
        BigInt numberOfPermutations() const; 
        std::string currentPermutation() const; 
        std::string firstPermutation() const;
        std::string lastPermutation() const; 
        std::string nextPermutation();  
        std::string prevPermutation(); 
        bool hasNext() const;  
        bool hasPrev() const; 

    private:
        std::string toString(T[]) const; 
        std::string next(T, T);  
        std::string prev(T, T);  
        bool equal(T[], T[]) const; 
        void reverse(T[]) const;
};

#endif
