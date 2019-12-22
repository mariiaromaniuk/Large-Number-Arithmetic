 /*
 main.cpp
 Large Integer
 
 Created by Mariia Romaniuk
 
 Large number arithmetic using doubly linked list - the implementation of the class
 LargeInt which uses a dynamic physical structure to store the individual digits of a
 very large integers, and provide arithmetic operations that can be performed on them.
 Implementation of the huge integer type encapsulated as a C++ class, aggregating a
 list object for the internal representation of the huge integer value. Huge integers
 may be positive or negative (or zero).
 
 In particular, the class include:
 - A default constructor
 - Operator functions to overload the operators +, -, *, /, %
 - Operator functions to overload the operators ==, <, <=, >, >=
 - An operator function to overload the operator <<
 - An operator function to overload the operator >>
 */


#include "LargeInteger.hpp"
#include <string>
#include <iostream>
using namespace std;

int main(){
    
    LargeInt a, b, c;
    char op;
    
    cout << "Enter first number: " << endl;
    cin >> a;
    
    cout << "Enter second number: " << endl;
    cin >> b;
    
    cout << "Choose an operator (+,-,*,/,%)" << endl;
    cin >> op;
    
    if(op == '+')
        c = a + b;
    else if(op == '-')
        c = a - b;
    else if(op == '*')
        c = a * b;
    else if(op == '/')
        c = a / b;
    else if(op == '%')
        c = a % b;
    else
        exit(0);
    
    cout << "\nResult: ";
    cout << c << endl;
    
    return 0;
    
}
