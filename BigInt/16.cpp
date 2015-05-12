/*
#------------------------------------------------------------------------------
# PROJECT EULER
# PROBLEM 16
#------------------------------------------------------------------------------
# 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
#
# What is the sum of the digits of the number 2^1000?
#------------------------------------------------------------------------------
# SOLUTION: 1366
#------------------------------------------------------------------------------
*/

#include <iostream>
#include "BigInt.cpp"
using namespace std;

int main(){
    BigInt num = BigInt("2").pow(1000);
    string numString = num.toString();
    int sum = 0;
    for (int i = 0; i < numString.length(); i++){
        sum += numString[i]-'0';
    }
    cout << sum << endl;
    return 0;
}
