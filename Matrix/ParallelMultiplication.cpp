#include "ParallelMatrix.h"
#include <iostream> 
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, char* argv[]) { 
    const int CORES = 4;
    
    const int N = atoi(argv[2]);
    const int M = atoi(argv[3]);
    
    cout << endl;
    cout << setw(35) << left << "Dimension of matrices" << N << " x " << N << endl;
    cout << setw(35) << left << "Dimension of blocks" << M << " x " << M << endl;
    cout << setw(35) << left << "Number of threads" << (N*N)/(M*M) << endl;
    cout << setw(35) << left << "Number of blocks per thread" << 2*N/M << endl;
    
    Matrix<int> A(N, N);
    Matrix<int> B(N, N);
    
    srand(time(NULL));
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) {            
            A.setEntry(i, j, int(rand() % 10));
            B.setEntry(i, j, int(rand() % 10));
        }
    }
    
    clock_t start, end;
    
    start = clock();
    Matrix<int> p_matrix = p_mul(A, B, M);
    end = clock();
    cout << setw(35) << left << "Parallel Time" << double(end - start) / CLOCKS_PER_SEC / CORES << "s" << endl; 
                                                                                        //must divide by the amount of cores on my machine
                                                                                        //in order to get real time (as opposed to user time)
    start = clock();
    Matrix<int> s_matrix = A.mul(B);
    end = clock();
    cout << setw(35) << left << "Serial Time" << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    
    cout << setw(35) << left << "Parallel result == Serial result?" << p_matrix.equals(s_matrix) << endl << endl;
    
    return 0;
}
