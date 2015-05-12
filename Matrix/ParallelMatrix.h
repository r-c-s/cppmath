#include "Matrix.cpp"
#include <string.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
using namespace std;

template <class T> Matrix<T> p_mul(const Matrix<T>&, const Matrix<T>&, const int);
template <class T> void _p_mul(Matrix<T>, const Matrix<T>*, const Matrix<T>*, const int, const int, const int);
template <class T> Matrix<T> p_add(const Matrix<T>&, const Matrix<T>&, const int);
template <class T> void _p_add(Matrix<T>, const Matrix<T>&, const Matrix<T>&, const int, const int);

template <class T> Matrix<T> p_mul(const Matrix<T> &A, const Matrix<T> &B, const int M) {
    assert (A.canMultiplyWith(B));

    const int AN = A.getN();
    const int AM = A.getM();
    const int BN = B.getN();
    const int BM = B.getM();
    
    assert (AN % M == 0 && AM % M == 0 && BN % M == 0 && BM % M == 0);

    const int processCount = (AN*BM)/(M*M); //number of processes (threads)
    const int blockCount   = AN/M;          //number of blocks per process

    Matrix<T> C = Matrix<T>(AN, BM);
    
    boost::thread_group group; 
    
    //partition matrix and assign blocks to a _p_mul, and assign a _p_mul to a thread
    for (int i = 0; i < processCount; i++) { 
        const int row = (i/blockCount)*M;
        const int col = (i%blockCount)*M;
          
        Matrix<T>* blocksA = new Matrix<T>[blockCount];  //array of blocks for matrix A
        Matrix<T>* blocksB = new Matrix<T>[blockCount];  //array of blocks for matrix B
        for (int j = 0; j < blockCount; j++) {
            blocksA[j] = A.getBlock(row, j*M, M, M);
            blocksB[j] = B.getBlock(j*M, col, M, M); 
        } 
        
        group.create_thread(boost::bind(static_cast<void(*)(Matrix<T>, const Matrix<T>*, const Matrix<T>*, const int, const int, const int)>
                                       (&_p_mul), C, blocksA, blocksB, row, col, blockCount)); 
    } 
    group.join_all();
    
    return C;
} 

template <class T> void _p_mul(Matrix<T> C, const Matrix<T> *A, const Matrix<T> *B, const int i, const int j, const int size) {
    const int N = A[0].getN(); 
    const int M = size; 
    
    for (int k = 0; k < M; k++) { 
        C.setBlock(i, j, C.getBlock(i, j, N, N).add(A[k].mul(B[k])));
    } 
}

template <class T> Matrix<T> p_add(const Matrix<T> &A, const Matrix<T> &B, const int M) {
    const int N = A.getN();
    
    assert (N % M == 0);

    const int processCount = (N*N)/(M*M); //number of processes (threads) 

    Matrix<T> C = Matrix<T>(N, N); 

    boost::thread_group group; 
    
    //partition matrix and assign blocks to a _p_add, and assign a _p_add to a thread
    for (int i = 0; i < processCount*M; i+=M) {    
        const int row = (i/N)*M;
        const int col = i%N;
                 
        group.create_thread(boost::bind(static_cast<void(*)(Matrix<T>, const Matrix<T>&, const Matrix<T>&, const int, const int)>
                                       (&_p_add), C, A.getBlock(row, col, M, M), B.getBlock(row, col, M, M), row, col)); 
    } 
    group.join_all();
    
    return C;
} 

template <class T> void _p_add(Matrix<T> C, const Matrix<T> &a, const Matrix<T> &b, const int i, const int j) {
    C.setBlock(i, j, a.add(b));
}
