#include "Matrix.cpp"
#include "Rational.cpp"
#include <iostream> 
#include <stdlib.h>
#include <time.h>
using namespace std;

int main() { 
    const int N = 4;
    
    Matrix<Rational> A(N, N);
    Matrix<double>   B(N, N);
    
    srand(time(NULL));
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) {
            int entry = rand() % 10;
            
            A.setEntry(i, j, Rational(entry));
            B.setEntry(i, j,   double(entry));
        }
    }
    
    cout << endl << "Two identical matrices with different data types." << endl << endl;
    cout << "-------------------------------------------------" << endl << endl;
    
    cout << "Matrix<Rational> A:" << endl;
    cout << A << endl;
    
    cout << "A.inverse():" << endl;
    cout << A.inverse() << endl;
    
    cout << "A * A.inverse():" << endl;
    cout << (A * A.inverse()) << endl;
    
    cout << "Theorem: A * A.inverse() == A.identity() ??? -> ";
    cout << (A * A.inverse() == A.identity()) << endl << endl;
    
    cout << "-------------------------------------------------" << endl << endl;
    cout << "Matrix<double> B:" << endl;
    cout << B << endl;
    
    cout << "B.inverse():" << endl;
    cout << B.inverse() << endl;
    
    cout << "B * B.inverse():" << endl;
    cout << (B * B.inverse()) << endl;
    
    cout << "Theorem: B * B.inverse() == B.identity() ??? -> ";
    cout << (B * B.inverse() == B.identity()) << endl << endl << endl;
    
    return 0;
}

