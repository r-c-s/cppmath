#include <iostream>
#include <sstream>
#include "Permutation.h"
#include "MergeSort.cpp"
using namespace std;

template <class T> Permutation<T>::Permutation(T* d, T l) {
    size = l;

    items = new T[size];
    firstPerm = new T[size];
    for (int i = 0; i < size; i++){
        items[i] = d[i];
        firstPerm[i] = d[i];
    }
    
    MergeSort<T>(firstPerm, size);

    lastPerm = new T[size];
    for (int i = 0; i < size; i++) {
        lastPerm[i] = firstPerm[i];
    }
    //lastPerm permutation is the reverse of firstPerm
    reverse(lastPerm);
}

template <class T> BigInt Permutation<T>::numberOfPermutations() const {
    stringstream l;
    l << size;
    return BigInt(l.str()).fact();
}

template <class T> string Permutation<T>::currentPermutation() const {
    return toString(items);
}

template <class T> string Permutation<T>::firstPermutation() const {
    return toString(firstPerm);
}

template <class T> string Permutation<T>::lastPermutation() const {
    return toString(lastPerm);
}

template <class T> string Permutation<T>::nextPermutation() {
    return next(size-2, size);
}

template <class T> string Permutation<T>::next(T i, T j) {
    if(items[i] < items[i+1]){
        int save = j;
        while (items[i] > items[--j]);
        T temp = items[j];
        items[j] = items[i];
        items[i] = temp;
        j = --save;
        while(i+1 <= j){
            temp = items[i+1];
            items[1+i++] = items[j];
            items[j--] = temp;
        }
        return currentPermutation();
    }
    return next(--i, j);
}

template <class T> bool Permutation<T>::hasNext() const {
    return !equal(items, lastPerm);
}

template <class T> string Permutation<T>::prevPermutation(){
    return prev(size-2, size);
}

template <class T> string Permutation<T>::prev(T i, T j){
    if(items[i] > items[i+1]){
        int save = j;
        while (items[i] < items[--j]);
        T temp = items[j];
        items[j] = items[i];
        items[i] = temp;
        j = --save;
        while(i+1 < j){
            temp = items[i+1];
            items[1+i++] = items[j];
            items[j--] = temp;
        }
        return currentPermutation();
    }
    return prev(--i, j);
}

template <class T> bool Permutation<T>::hasPrev() const {
    return !equal(items, firstPerm);
} 

template <class T> string Permutation<T>::toString(T* d) const {
    stringstream s;
    for (int i = 0; i < size; i++){
        s << d[i];
    }
    return s.str();
}

template <class T> void Permutation<T>::reverse(T a[]) const {
    //copy of a
    T b[size];
    for (int i = 0; i < size; i++){
        b[i] = a[i];
    }
    for (int i = 0; i < size; i++){
        a[i] = b[size-1-i];
    }
}

template <class T> bool Permutation<T>::equal(T a[], T b[]) const {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
} 
