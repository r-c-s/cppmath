/*
#------------------------------------------------------------------------------
# PROJECT EULER
# PROBLEM 24
#------------------------------------------------------------------------------
# A permutation is an ordered arrangement of objects. For example, 3124 is one 
# possible permutation of the digits 1, 2, 3 and 4. If all of the permutations 
# are listed numerically or alphabetically, we call it lexicographic order. 
# The lexicographic permutations of 0, 1 and 2 are:
#
# 012   021   102   120   201   210
#
# What is the millionth lexicographic permutation of the digits 
# 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
#------------------------------------------------------------------------------
# SOLUTION: 2783915460
#------------------------------------------------------------------------------
# as -32 24.s -o 24.o
# gcc -m32 24.o -o 24
#------------------------------------------------------------------------------
*/

#include <iostream>
#include "Permutation.cpp"
using namespace std;

int main(){
    //Finds the millionth permutation of 0123456789
    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Permutation<int> m = Permutation<int>(numbers, 10);
    
    for (int i = 1; i < 1000000; i++) {
        m.nextPermutation();
    }
    cout << m.currentPermutation() << endl; //millionth permutation

    return 0;
}
