#include <iostream>
#include <iomanip>
#include "Permutation.cpp"
using namespace std; 

int main(){ 
    //Generates all next permutations of 012
    int nums[] = {0, 1, 2};
    Permutation<int> n = Permutation<int>(nums, 3);
    
    cout << left << setw(4) << n.firstPermutation();
    while(n.hasNext()){
        cout << left << setw(4) << n.nextPermutation();
    }
    cout << endl << endl;

    //Generates all previous permutations of DCBA
    char letters[] = {'D', 'C', 'B', 'A'};
    Permutation<char> l = Permutation<char>(letters, 4);
    
    cout << left << setw(5) << l.lastPermutation();
    while(l.hasPrev()){
        cout << left << setw(5) << l.prevPermutation();
    }
    cout << endl << endl;
    
    //Finds the millionth permutation of 0123456789
    int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Permutation<int> m = Permutation<int>(numbers, 10);
    
    for (int i = 1; i < 1000000; i++) {
        m.nextPermutation();
    }
    cout << m.currentPermutation() << endl << endl; //millionth permutation
    
    cout << m.numberOfPermutations() << endl;       //number of permutations = N!
    
    return 0;
}
