#include <iostream>
#include "BigInt.cpp"

int main(){
    BigInt a("123456789876543212345678987654321");
    BigInt b("987654321234567898765432123456789");
    
    cout << endl;
 
    cout << a << " + " << b << " = " << a.add(b) << endl << endl;

    cout << a << " - " << b << " = " << a.sub(b) << endl << endl;
    
    cout << a << " * " << b << " = " << a.mul(b) << endl << endl;
    
    cout << a << " / " << b << " = " << a.div(b) << endl << endl; 

    cout << a << " ^ 6 = " << a.pow(6) << endl << endl;
    
    cout << "2 ^ 5000 = " << BigInt("2").pow(5000) << endl << endl;
    
    cout << "1000 ! = " << BigInt("1000").fact() << endl << endl;
    
    return 0;
}
