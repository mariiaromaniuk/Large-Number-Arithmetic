//
//  LargeInteger.hpp
//  Large Integer
//
//  Created by Mariia Romaniuk
//

#ifndef LargeInteger_hpp
#define LargeInteger_hpp

#include "DoublyLinkedList.hpp"
#include <stdio.h>
#include <iostream>
using namespace std;


class LargeInt {
    
public:
    LargeInt();
    
    // Input & Output Operators
    friend ostream& operator<<(ostream& out, LargeInt&);
    friend istream& operator>>(istream& in, LargeInt&);
    
    // Arithmetic Operators
    LargeInt operator+(LargeInt& b);
    LargeInt operator-(LargeInt& b);
    LargeInt operator/(LargeInt& b);
    LargeInt operator*(LargeInt& b);
    LargeInt operator%(LargeInt& b);
    
    // Comparison Operators
    bool operator==(LargeInt& b);
    bool operator>=(LargeInt& b);
    bool operator<=(LargeInt& b);
    bool operator>(LargeInt& b);
    bool operator<(LargeInt& b);
    
    // Check if negative sign is entered
    int negativeCheck(bool num1, bool num2);
    
private:
    DLinkedList<int> add(LargeInt& a, LargeInt& b);
    int size;
    bool isNeg;
    DLinkedList<int> list1;
    
};

#endif /* LargeInteger_hpp */
