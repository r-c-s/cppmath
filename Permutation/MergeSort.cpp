#include "MergeSort.h"

template <class T> MergeSort<T>::MergeSort(T a[], int size) {
    T aux[size];
    sort(a, aux, 0, size-1);
}

template <class T> void MergeSort<T>::sort(T a[], T aux[], T lo, T hi) {
    if (hi <= lo) return;
    int mid = (lo + hi) / 2;
    sort(a, aux, lo, mid);
    sort(a, aux, mid+1, hi);
    merge(a, aux, lo, mid, hi);
}

template <class T> void MergeSort<T>::merge(T a[], T aux[], T lo, T mid, T hi) {
    // copy region to aux array
    for (T i=lo; i<=hi; i++) {
        aux[i] = a[i];
    }
    // merge the two sorted subregions back To the input array
    int i = lo;
    int j = mid+1;
    for (T k=lo; k<=hi; k++) {
        if      (hi <j)            a[k] = aux[i++];
        else if (mid<i)            a[k] = aux[j++];
        else if (aux[j] < aux[i])  a[k] = aux[j++];
        else                       a[k] = aux[i++];
    }
}

template <class T> void MergeSort<T>::exch(T a[], T i, T j) {
    T t = a[i];
    a[i] = a[j];
    a[j] = t;
}
