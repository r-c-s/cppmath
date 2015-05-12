#include <iostream> 
#include <stdlib.h>  
#include <cassert>
#include "BigInt.h"
using namespace std;

extern "C" long factorial(long*);
extern "C" long power(long*);

const BigInt ZERO("0");
const BigInt  ONE("1");

BigInt::BigInt() {
    setValue("0"); 
}

BigInt::BigInt(string n) {
    setValue(n); 
}

string BigInt::toString() const {
    return (positive ? "" : "-") + value;
}

BigInt BigInt::add(const BigInt &b) const { 
    if(positive && !b.positive) return sub(b.abs());
    if(!positive && b.positive) return b.sub(abs());
    
    string bigInts[2] = {value, b.value};
    
    int len = value.length() >= b.value.length() ? value.length() : b.value.length();

    const int sLen = len+1;
    int s[sLen];
    for (int i = 0; i < sLen; i++) s[i] = 0;

    for (int j = 0; j < len; j++) {
        for(int i = 0; i < 2; i++){
            int index = bigInts[i].length()-1-j;
            if(index < 0) continue;
            s[sLen-1-j] += toInt(bigInts[i][index]);
        }
    }
     
    string result = (!positive && !b.positive ? "-" : "") + parseArray(s, sLen);  
    
    return BigInt(result);
}

BigInt BigInt::sub(const BigInt &b) const { 
    if(positive && !b.positive) return add(b.abs());
    if(!positive && b.positive) return BigInt("-"+b.add(abs()).value);
    if(!positive && !b.positive) return b.abs().sub(abs());
    
    bool GE = abs().ge(b.abs());
    string bigIntA = GE ?   value : b.value;
    string bigIntB = GE ? b.value :   value;
    
    int len = bigIntA.length();

    const int sLen = len+1;
    int s[sLen];
    for (int i = 0; i < sLen; i++) s[i] = 0;

    for (int j = 0; j < len; j++) {
        s[sLen-1-j] = toInt(bigIntA[len-1-j]);
        int index = bigIntB.length()-1-j;
        if(index < 0) continue;
        s[sLen-1-j] -= toInt(bigIntB[index]);
    }
     
    string result = (GE ? "" : "-") + parseArray(s, sLen);  
    
    return BigInt(result);
}

BigInt BigInt::mul(const BigInt &b) const {        
    const int len = value.length() + b.value.length() - 1;
    int s[len];
    for (int i = 0; i < len; i++) s[i] = 0;

    for (int j = value.length()-1; j >= 0; j--){
        int num = toInt(value[j]);
        for(int i = b.value.length()-1; i >= 0; i--){
            s[i+j] += num * toInt(b.value[i]);
        }
    }
    
    string result = (!positive ^ !b.positive ? "-" : "") + parseArray(s, len);

    return BigInt(result);
}

BigInt BigInt::div(const BigInt &b) const {
    assert(!b.eq(ZERO));
    
    string bigIntA =   value;
    string bigIntB = b.value;

    const int len = value.length();

    int s[len];
    for (int i = 0; i < len; i++) s[i] = 0; 
    
    for (int j = 0; j < len; j++){
        s[j] = 0;
        BigInt current(bigIntA.substr(0, j+1));
        if(current.le(bigIntB)) continue;
        while(current.ge(b.abs().mul(BigInt(toString(++s[j]))))); 
        string remainder = current.sub(b.abs().mul(BigInt(toString(--s[j])))).value; 
        bigIntA = remainder + bigIntA.substr(j+1, value.length());
        while (bigIntA.length() < value.length()) bigIntA = "0" + bigIntA;
        if(BigInt(bigIntA).le(ZERO)) break; 
    } 
    
    string result = (!positive ^ !b.positive ? "-" : "") + parseArray(s, len);

    return BigInt(result);
}

BigInt BigInt::abs() const { 
    return BigInt(value);
}

BigInt BigInt::fact() const {
    if (eq(ZERO)) return BigInt("1");
    
    assert(positive);
    unsigned long number = toLong(value);
    assert(toString(number) == value);
    
    long* ptr1 = (long*)malloc(number*2*sizeof(long));
    ptr1[0] = number;
    long* ptr2 = (long*)factorial(ptr1); 
    
    string s = "";
    long digit = 0;
    while ((digit = (long)*ptr2) != -1) { 
        string num = toString(digit);
        while (num.length() < 8) num = "0" + num; 
        s = num + s;
        ptr2++;
    } 
    
    free(ptr1);
    return BigInt(s);
}

BigInt BigInt::pow2(int n) const {
    if(n == 0) return ONE;
    if(n == 1) return BigInt((positive ? "" : "-") + value);
    BigInt total(value);
    for (int i = 1; i < n; i++){
        total = mul(total);
    }
    if (!positive && n % 2 == 1) total = BigInt("-" + total.value);
    return total;
} 

BigInt BigInt::pow(int n) const {
    assert(n >= 0);
    if (eq(ZERO)) return BigInt("1");
    if (eq(ONE))  return BigInt((positive ? "" : "-") + value);
     
    unsigned long number = toLong(value);
    if (toString(number) != value) return pow2(n); //number did not fit into 64 bits
    
    long* ptr1 = (long*)malloc(n*2*sizeof(long));
    ptr1[0] = number;
    ptr1[1] = n;
    long* ptr2 = (long*)power(ptr1); 
    
    string s = "";
    long digit = 0;
    while ((digit = (long)*ptr2) != -1) { 
        string num = toString(digit);
        while (num.length() < 8) num = "0" + num; 
        s = num + s;
        ptr2++;
    } 
    
    free(ptr1);
    return BigInt(((!positive && n % 2 == 1) ? "-" : "") + s);
} 

BigInt BigInt::mod(const BigInt &b) const {
    return sub(b.mul(div(b)));
}


int BigInt::compareTo(const BigInt &b) const {
    if (value == b.value) return  0;
    if (lessThan(b))      return -1;
    else                  return  1;
}

bool BigInt::lessThan(const BigInt &b) const { 
    if(positive && !b.positive) return false;
    if(!positive && b.positive) return true;
    if(!positive && !b.positive) return !abs().lessThan(b.abs());
    string A = value;
    string B = b.value;
    if(A.length() < B.length()) return true;
    if(A.length() > B.length()) return false;
    for (int i = 0; i < A.length(); i++){
        if(A[i] < B[i]) return true;
        if(A[i] > B[i]) return false;
    }
    return false;
}

void BigInt::setValue(string n) {
    positive = n[0] == '-' ? false : true; 
    value    = trim(n);
    assert(isANum(value));
}

bool BigInt::isANum(string n) const {
    for (int i = 0; i < n.length(); i++){
        if(toInt(n[i]) < 0 || toInt(n[i]) > 9) return false;
    }
    return true;
}

string BigInt::trim(string a) const {
    int i = 0;
    for (i; i < a.length()-1; i++){
        if(a[i] != '0' && a[i] != '-') break;
    }
    return a.substr(i, a.length());
}

string BigInt::parseArray(int* s, const int len) const {
    for (int i = len-1; i > 0 ; i--){ 
        if(s[i] < 0){
            s[i] += 10;
            s[i-1]--;
            continue;
        } 
        if(s[i] <= 9) continue;
        s[i-1] += s[i] / 10;
        s[i] %= 10;
    }
    string result = "";
    for (int i = 0; i < len; i++){
        stringstream ss;
        ss << s[i];
        result += ss.str();
    }
    return result;
}

string BigInt::toString(int n) const {
    stringstream s;
    s << n;
    return s.str();
}

unsigned long BigInt::toLong(string s) const {
    stringstream ss(s);
    long n = 0;
    ss >> n;
    return n;
}

int BigInt::toInt(string s) const {
    stringstream ss(s);
    int n = 0;
    ss >> n;
    return n;
}

int BigInt::toInt(char c) const {
    return c - '0';
}
