#include "Matrix.h" 
#include <iostream> 
#include <cmath>
#include <iomanip>
#include <cassert>
using namespace std;

template <class T> Matrix<T>::Matrix(int n, int m){
    N = n;
    M = m;
    matrix = new T[N*M];
    for (int i = 0; i < N*M; i++) {
        matrix[i] = 0;
    }
}

template <class T> Matrix<T>::Matrix(T* mx, int n, int m) {
    matrix = mx;
    N = n;
    M = m;
}

template <class T> int Matrix<T>::getN() const {
    return N;
}

template <class T> int Matrix<T>::getM() const {
    return M;
}

template <class T> T Matrix<T>::getEntry(int i, int j) const {
    return matrix[i*M + j];
}

template <class T> void Matrix<T>::setEntry(int i, int j, T t) {
    matrix[i*M + j] = t;
}

template <class T> Matrix<T> Matrix<T>::getBlock(int a, int b, int n, int m) const {
    assert (a+n <= N && b+m <= M);

    Matrix<T> block = Matrix<T>(n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            block.matrix[i*m + j] = matrix[M*(i+a) + j+b];
        } 
    }
    return block;
}

template <class T> void Matrix<T>::setBlock(int a, int b, const Matrix &m) {
    assert (m.N <= N-a && m.M <= M-b);

    for (int i = 0; i < m.N; i++) {
        for (int j = 0; j < m.M; j++) {
            matrix[M*(i+a) + j+b] = m.matrix[i*m.M + j];
        } 
    }
}

template <class T> Matrix<T> Matrix<T>::add(const Matrix &m) const {
    assert (sameDimensionsAs(m));
    
    Matrix<T> result = Matrix<T>(N, M);

    for (int i = 0; i < N*M; i+=M) {
        for (int j = 0; j < M; j++) {
            result.matrix[i + j] = matrix[i + j] + m.matrix[i + j];
        }
    }   
    return result;        
}

template <class T> Matrix<T> Matrix<T>::sub(const Matrix &m) const {
    return add(m.mul(T(-1))); 
}

template <class T> Matrix<T> Matrix<T>::mul(const Matrix &m) const {
    assert (canMultiplyWith(m));

    Matrix<T> result = Matrix<T>(N, m.M);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                result.matrix[k*m.M + i] = result.matrix[k*m.M + i] + (matrix[k*M + j] * m.matrix[j*m.M + i]); 
            }
        }
    } 
    return result;
}

template <class T> Matrix<T> Matrix<T>::div(const Matrix &m) const {
    return mul(m.inverse());
}

template <class T> Matrix<T> Matrix<T>::mul(const T &t) const {
    Matrix<T> result = Matrix<T>(N, M);

    for (int i = 0; i < N*M; i+=M) { 
        result.matrix[i] = matrix[i] * t; 
    }  
    return result;
}

template <class T> T Matrix<T>::determinant() const {
    assert (isSquare());
     
    if (N == 2)
        return (matrix[0*M + 0] * matrix[1*M + 1]) - (matrix[0*M + 1] * matrix[1*M + 0]);

    T det = T(0);
    for (int i = 0; i < M; i++) {
        det = det + T((int) pow(-1, i)) * matrix[i] * 
                    getBlock(1, 0, N-1, i).combine(getBlock(1, i+1, N-1, N-1-i)).determinant();
    }
    return det;
}

template <class T> Matrix<T> Matrix<T>::combine(const Matrix &m) const {
    assert (N == m.N);

    Matrix<T> combined = Matrix<T>(N, M+m.M);

    if (0 < M)   combined.setBlock(0, 0, *this);
    if (0 < m.M) combined.setBlock(0, M, m);

    return combined;
}

template <class T> Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> transposed = Matrix<T>(M, N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            transposed.matrix[i*N + j] = matrix[j*M + i];
        }
    } 
    return transposed;
}

template <class T> Matrix<T> Matrix<T>::identity() const {
    assert (isSquare());

    Matrix<T> identity = Matrix<T>(N, N);

    for (int i = 0; i < N; i++) {
        identity.matrix[i*M + i] = T(1);
    } 
    return identity;    
}

template <class T> Matrix<T> Matrix<T>::inverse() const {
    assert (determinant() != T(0));
    Matrix<T> cpmatrix = copy();
    Matrix<T> identity = Matrix<T>(N, N).identity();
    
    for (int i = 0; i < M; i++) {
        int j = i;
        int maxIndex = i;
        T maxVal = cpmatrix.getEntry(i, j);
        for (int k = i+1; k < M; k++) {
            if (abs(double(cpmatrix.getEntry(k, j))) > abs(double(maxVal))) {
                maxVal = cpmatrix.getEntry(k, j);
                maxIndex = k;
            }
        }
        if (maxVal != T(0)) { 
            Matrix<T> temp = cpmatrix.getBlock(i, 0, 1, M);
            cpmatrix.setBlock(i, 0, cpmatrix.getBlock(maxIndex, 0, 1, M));
            cpmatrix.setBlock(maxIndex, 0, temp); 
            temp = identity.getBlock(i, 0, 1, M);;
            identity.setBlock(i, 0, identity.getBlock(maxIndex, 0, 1, M));
            identity.setBlock(maxIndex, 0, temp);
            for (int l = 0; l < M; l++) {
                cpmatrix.setEntry(i, l, cpmatrix.getEntry(i, l)/maxVal);
                identity.setEntry(i, l, identity.getEntry(i, l)/maxVal);
            }
        }
        for (int m = 0; m < M; m++) {
            if (m == i) continue;
            T factor = cpmatrix.getEntry(m, i); 
            for (int n = 0; n < M; n++) {
                cpmatrix.setEntry(m, n, cpmatrix.getEntry(m, n) - (factor * cpmatrix.getEntry(i, n)));
                identity.setEntry(m, n, identity.getEntry(m, n) - (factor * identity.getEntry(i, n)));
            }
        }
    }
    return identity;
}

template <class T> Matrix<T> Matrix<T>::copy() const {
    Matrix<T> copy(N, M);
    for (int i = 0; i < N*M; i++) {
        copy.matrix[i] = matrix[i];
    }
    return copy;
}

template <class T> bool Matrix<T>::isSquare() const {
    return N == M;
}

template <class T> bool Matrix<T>::equals(const Matrix &m) const {
    if (!sameDimensionsAs(m)) return false;
    for (int i = 0; i < N*M; i++) { 
        if (matrix[i] != m.matrix[i]) 
            return false;
    }
    return true;
}

template <class T> bool Matrix<T>::operator==(const Matrix &m) const {
    return equals(m);
}

template <class T> bool Matrix<T>::canMultiplyWith(const Matrix &m) const {
    return M == m.N;
}

template <class T> bool Matrix<T>::sameDimensionsAs(const Matrix &m) const {
    return N == m.N && M == m.M;
}

template <class T> string Matrix<T>::toString() const {
    string matrixString = "";
    for (int i = 0; i < N*M; i+=M) {
        for (int j = 0; j < M; j++) {
            matrixString += format(matrix[i + j], j);
        }
        matrixString += "\n";
    }
    return matrixString;
}

template <class T> string Matrix<T>::format(T t, int j) const {
    stringstream s;
    s << setw(width(j)+2) << t;
    return s.str();
}

template <class T> int Matrix<T>::width(int j) const {
    int width = 0;
    for (int i = 0; i < N*M; i+=M) {
        stringstream s;
        s << matrix[i + j];
        if (s.str().length() > width) width = s.str().length();
    }
    return width;
}
