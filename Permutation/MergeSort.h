#ifndef MERGESORT_H
#define MERGESORT_H

template <class T> class MergeSort {
        T* data;
        int size;
        
    public:
        MergeSort(T[], int);  
        
    private:
        void sort(T[], T[], T, T);
        void merge(T[], T[], T, T, T);
        void exch(T[], T, T);
};

#endif
