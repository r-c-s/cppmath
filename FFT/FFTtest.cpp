#include "FFT.h"
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);

    double* polynom = new double[N];

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        polynom[i] = double(rand() % 10);
    }

    const int size = nextPowerOfTwo(N);

    Complex* fft_res = FFT(polynom, N);
    double* ifft_res = IFFT(fft_res, size);

    cout << endl;
 
    cout << setw(25) <<             "Polynomial:   ";              
    for (int i = 0; i <    N; i++) cout <<  polynom[i] << " ";    cout << endl << endl;


    cout << setw(25) <<        "FFT(Polynomial):   ";         
    for (int i = 0; i < size; i++) cout <<  fft_res[i] << " ";    cout << endl << endl;


    cout << setw(25) <<  "IFFT(FFT(Polynomial)):   ";   
    for (int i = 0; i < size; i++) cout << ifft_res[i] << " ";    cout << endl << endl;


    cout << "IFFT(FFT(Polynomial)) == Polynomial ? ";  
    for (int i = 0; i < N; i++) {
        if (polynom[i] - ifft_res[i] > 0.00001) { cout << "FALSE\n\n"; break; }
        if (i == N-1)                             cout << "TRUE\n\n";
    } 

    return 0;
}
