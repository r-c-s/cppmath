#ifndef MATRIX_H
#define MATRIX_H

#include "Arithmetical.h" 

template <class T> class Matrix : public Arithmetical<Matrix<T> > { 
    private:
        T* matrix;
        int N;
        int M;
        int width(int) const;
        std::string format(T, int) const;
        
    public:
        Matrix() {}
        Matrix(const int, const int);
        Matrix(T*, const int, const int);
        int getN() const;
        int getM() const;
        T getEntry(int, int) const;
        void setEntry(int, int, T);
        Matrix getBlock(int, int, int, int) const;
        void setBlock(int, int, const Matrix&);
        Matrix add(const Matrix&) const;
        Matrix sub(const Matrix&) const;
        Matrix mul(const Matrix&) const;
        Matrix div(const Matrix&) const;
        Matrix mul(const T&) const;
        T determinant() const;
        Matrix combine(const Matrix&) const;
        Matrix transpose() const;
        Matrix identity() const;
        Matrix inverse() const;
        Matrix copy() const;
        bool isSquare() const;
        bool equals(const Matrix&) const;
        bool operator==(const Matrix&) const;
        bool canMultiplyWith(const Matrix&) const;
        bool sameDimensionsAs(const Matrix&) const;
        std::string toString() const;    
};

#endif

