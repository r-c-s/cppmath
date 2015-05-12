/*
#------------------------------------------------------------------------------
# PROJECT EULER
# PROBLEM 15
#------------------------------------------------------------------------------
# Starting in the top left corner of a 22 grid, there are 6 routes (without 
# backtracking) to the bottom right corner.
#
# How many routes are there through a 2020 grid?.
#------------------------------------------------------------------------------
# SOLUTION: 137846528820
#------------------------------------------------------------------------------
*/

#include <iostream>
#include <sstream>
#include "BigInt.cpp"
using namespace std;

int main(){
    BigInt a = BigInt("40").fact();
    BigInt b = BigInt("20").fact().pow(2);
    BigInt c = a / b;
    cout << c.toString() << endl;
    return 0;
}
