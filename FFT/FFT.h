#include "Complex.cpp"
#include <cmath>
#include <cassert>

Complex* FFT(double*, const int);  
double* IFFT(Complex*, const int);
Complex* rootsOfUnity(int n);
bool isPowerOfTwo(int n);
double* addZeroes(double*, const int, const int);
int nextPowerOfTwo(const int);

Complex* FFT(double* d, const int n) {
    const int dim  = nextPowerOfTwo(n);
    double* vector = addZeroes(d, n, dim);
    
    Complex* fft_res = new Complex[dim];
    Complex  root    = rootsOfUnity(dim)[0];

    for (int i = 0; i < dim; i++) {
        fft_res[i] = Complex(vector[i], 0);
    }

    int size  = dim;
    int gap   = size/2;
    int parts = 1;

    while(size > 1) {
        for (int j = 0; j < parts; j++) {
            for (int i = j*size; i < j*size+gap; i++) {
                Complex temp   =  fft_res[i] + fft_res[i+gap];
                fft_res[i+gap] = (fft_res[i] - fft_res[i+gap]) * ((size == 4 && gap == 2 && i % 2 == 1) ? root : Complex(1, 0));
                fft_res[i]     = temp;
            } 
        } 
        size  /= 2;
        gap   /= 2;
        parts *= 2;
    }

    return fft_res;
}

double* IFFT(Complex* fft_res, const int dim) {
    Complex* ifft_res_c = new Complex[dim];
    Complex  root       = rootsOfUnity(dim)[dim-2];

    for (int i = 0; i < dim; i++) {
        ifft_res_c[i] = fft_res[i];
    }

    int size  = 2;
    int gap   = 1;
    int parts = dim/2;

    while(size <= dim) {
        for (int j = 0; j < parts; j++) {
            for (int i = j*size; i < j*size+gap; i++) {
                Complex temp      =  ifft_res_c[i] + ifft_res_c[i+gap];
                ifft_res_c[i+gap] = (ifft_res_c[i] - ifft_res_c[i+gap]) * ((size == 2 && gap == 1 && j % 2 == 1) ? root : Complex(1, 0));
                ifft_res_c[i]     = temp;
            } 
        } 
        size  *= 2;
        gap   *= 2;
        parts /= 2;
    }

    double*  ifft_res   = new double[dim];

    for (int i = 0; i < dim; i++) {
        ifft_res[i] = ifft_res_c[i].getReal() / dim;
    }

    return ifft_res;
}

Complex* rootsOfUnity(int n) {
    assert(isPowerOfTwo(n));
    Complex* roots = new Complex[n]; 
    
    const double PI  = atan(1.0)*4;
    const double rad = (2*PI)/n;
    
    for (int i = 0; i < n; i++) {
        roots[i] = Complex(cos((i+1)*rad), sin((i+1)*rad));
    }
    
    return roots;
}

bool isPowerOfTwo(int n) { 
    return (n > 0) && (n & (n - 1)) == 0;
}

double* addZeroes(double* c, const int n, const int m) {
    double* v = new double[m];
    for (int i = 0; i < n; i++) v[i] = c[i];
    for (int i = n; i < m; i++) v[i] = 0;
    return v;
}

int nextPowerOfTwo(const int n) {
    int power = 0;
    for (int i = 0; true; i++) {
        if ((power = pow(2, i)) >= n)
            return power;
    }
}
