//
//  LargeInteger.cpp
//  Large Integer
//
//  Created by Mariia Romaniuk
//

#include "LargeInteger.hpp"
#include "DoublyLinkedList.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;



LargeInt::LargeInt(){    // Constructor
    size = 0;
    isNeg = false;
    
}


//Overload of input stream to attain numbers
istream& operator>> (istream& in, LargeInt& number){
    string str;
    getline(in,str);
    
    number.size = str.size();
    number.isNeg = false;
    
    for (int i = 0; i < number.size; i++){
        if (str[i] == '-'){
            number.isNeg = true;
            number.list1.insertFront(str[i+1] - '0');
            i++;
        }
        else
            number.list1.insertFront(str[i] - '0');
    }
    return in;
}


// Overload of output operator to output result
ostream& operator<< (ostream& out, LargeInt& number){
    
    if(number.isNeg == true)
        out << "-";
    else
        out << "";
    
    for (auto itr = number.list1.begin(); itr != number.list1.end(); itr++)
        cout << *itr;
    
    return out;
    
}


// Overload the operator "equal" to check if numbers are equivalent
bool LargeInt::operator== (LargeInt& b){
    
    bool isTrue = true;
    int count = 0;
    
    if (size != b.size)
        isTrue = false;
    else {
        auto itr = list1.begin();
        auto itr2 = b.list1.begin();
        
        while (count < b.size){
            if(itr != itr2)
                isTrue = false;
            break;
            itr++;
            itr2++;
        }
    }
    return isTrue;
}


// Overload the "less than" operator
bool LargeInt::operator< (LargeInt& b){
    
    bool isTrue = true;
    
    auto itr = list1.begin();
    auto itr2 = b.list1.begin();
    
    if (this->list1.getLength() < b.list1.getLength()){
        isTrue = true;
        
    } else if (this->list1.getLength() > b.list1.getLength()){
        isTrue = false;
        
    }
    else {
        for (int i = 0; i < list1.getLength(); i++){
            if (*itr < *itr2){
                isTrue = true;
                break;
            } else if (*itr == *itr2){
                isTrue = true;
            } else if (*itr > *itr2){
                isTrue = false;
                break;
            }
            itr++;itr2++;
        }
    }
    return isTrue;
}


// Overload the "greater than" operator
bool LargeInt::operator> (LargeInt& b){
    
    bool isTrue = true;
    
    auto itr = list1.begin();
    auto itr2 = b.list1.begin();
    
    if (this->list1.getLength() < b.list1.getLength()){
        isTrue = false;
    } else if (this->list1.getLength() > b.list1.getLength()){
        isTrue = true;
    } else if (*this == b) {
        isTrue = false;
    } else {
        for (int i = 0; i < list1.getLength(); i++){
            if (*itr == *itr2){
                isTrue = true;
                
            } else if (*itr < *itr2){
                isTrue = false;
                break;
            } else if (*itr > *itr2){
                isTrue = false;
                break;
            }
            itr++;itr2++;
        }
    }
    return isTrue;
}


// Overload the "greater than or equal to" operator
bool LargeInt::operator>= (LargeInt& b){
    bool isTrue = false;
    
    if (*this > b || *this == b)
        isTrue = true;
    
    return isTrue;
}


// Overload the "less than or equal to" operator
bool LargeInt::operator<= (LargeInt& b){
    bool isTrue = false;
    
    if (*this < b || *this == b)
        isTrue = true;
    
    return isTrue;
}


// Function to check if result chould be positive or negative number
int LargeInt::negativeCheck(bool num1, bool num2) {
    int res = 0;
    
    if (num1 && num2)  // Both numbers are negative
        res = 1;
    
    if (!num1 && num2)  // Number 2 is positive, Number 1 is negative
        res = 2;
    
    if (num1 && !num2)  // Number 1 is positive, Number 2 is negative
        res = 3;
    
    return res;
}


// Addition function to assist in multiplication method
DLinkedList<int> LargeInt::add(LargeInt& a, LargeInt& b) {
    DLinkedList<int> c;
    
    int count = 0;
    int carry = 0;
    int total = 0;
    int num = 0;
    int bigger = b.list1.getLength();
    
    
    // Check sizes of lists are equal.
    // If not - will distribute 0's to even out addition on operands.
    if (a.list1.getLength() != b.list1.getLength()){
        
        if (b.list1.getLength() > a.list1.getLength()){
            num = b.list1.getLength() - a.list1.getLength();
            
            while (num > 0){
                a.list1.insertBack(0);
                num--;
            }
        } else
            num = a.list1.getLength() - b.list1.getLength();
        
        bigger = a.list1.getLength();
        
        while (num > 0){
            b.list1.insertBack(0);
            num--;
        }
    }
    
    auto itr = a.list1.begin();
    auto itr2 = b.list1.begin();
    
    
    while (count < bigger ) {
        total = (*itr + *itr2);
        if (total > 9){
            total += carry;
            total -= 10;
            carry = 1;
            c.insertFront(total);
            if(b.size == 1 && size == 1)
                c.insertFront(carry);
        }
        else{
            total += carry;
            c.insertFront(total);
            carry = 0;
        }
        count++; itr++; itr2++;
    }
    return c;
}


// Addition Operator to add two large integers together
LargeInt LargeInt::operator+ (LargeInt& b){
    LargeInt c;
    int count = 0;
    int carry = 0;
    int total = 0;
    int num = 0;
    int bigger = b.list1.getLength();
    
    auto itr = list1.begin();
    auto itr2 = b.list1.begin();
    
    int res = negativeCheck(this->isNeg, b.isNeg);
    
    if (res == 1){
        total = (*itr + *itr2);
        c.isNeg = true;
    }
    if (res == 2){
        total = (*itr2 - *itr);
        c.isNeg = true;
        
        if (*itr <= *itr2)
            c.isNeg = false;
        else
            c.isNeg = true;
    }
    if (res == 3){
        c.isNeg = false;
        total = (*itr - *itr2);
    }
    else
        total = (*itr + *itr2);
    
    
    // Check sizes of lists are equal
    // If not - will distribute 0's to even out addition on operands.
    if (list1.getLength() != b.list1.getLength()){
        
        if (b.list1.getLength() > list1.getLength()){
            num = b.list1.getLength() - list1.getLength();
            
            while (num > 0){
                list1.insertBack(0);
                num--;
            }
        }
        else
            num = list1.getLength() - b.list1.getLength();
        bigger = list1.getLength();
        
        while(num > 0){
            b.list1.insertBack(0);
            num--;
        }
    }
    
    while (count < bigger) {
        if (res == 1){
            total = (*itr + *itr2);
            c.isNeg = true;
        }
        if(res == 2){
            total = (*itr2 - *itr);
            c.isNeg = true;
            
            if(*itr <= *itr2)
                c.isNeg = false;
            else
                c.isNeg = true;
        }
        if(res == 3){
            c.isNeg = false;
            total = (*itr - *itr2);
        } else
            total = (*itr + *itr2);
        if(total > 9){
            total += carry;
            total -= 10;
            carry = 1;
            c.list1.insertFront(total);
            if((b.size == 1 && size == 1)){
                c.list1.insertFront(carry);
            }
        }
        else {
            total += carry;
            c.list1.insertFront(total);
            carry = 0;
        }
        count++; itr++; itr2++;
    }
    if (carry == 1)
        c.list1.insertFront(carry);
    
    return c;
    
}


// Subtraction operator to subtract two large integers together
LargeInt LargeInt::operator- (LargeInt& b){
    LargeInt c;
    
    int count = 0;
    int carry = 0;
    int total = 0;
    int num = 0;
    int bigger = b.list1.getLength();
    
    int combo = negativeCheck(this->isNeg, b.isNeg);
    
    if(list1.getLength() != b.list1.getLength()) {
        
        if(b.list1.getLength() > list1.getLength())
        {
            num = b.list1.getLength() - list1.getLength();
            
            while(num > 0)
            {
                list1.insertBack(0);
                num--;
            }
        }
        else
            num = list1.getLength() - b.list1.getLength();
        bigger = list1.getLength();
        while(num > 0)
        {
            b.list1.insertBack(0);
            num--;
        }
    }
    
    auto itr = list1.begin();
    auto itr2 = b.list1.begin();
    
    while (count < bigger) {
        
        if(combo == 1){
            total = (*itr - *itr2);
            c.isNeg = true;
        }
        if(combo == 2){
            total = (*itr2 + *itr);
            c.isNeg = false;
        }
        if(combo == 3){
            c.isNeg = false;
            total = (*itr + *itr2);
            
        }
        else
            total = (*itr - *itr2);
        if (total < 0)
        {
            total += carry;
            total += 10;
            carry = -1;
            c.list1.insertFront(total);
        }
        
        else{
            
            total += carry;
            if(total < 0){
                total += 10;
                carry = -1;
                c.list1.insertFront(total);
            }
            else {
                c.list1.insertFront(total);
                carry = 0;
            }
        }
        count++; itr++; itr2++;
    }
    return c;
    
}


// Multiplication operator to multiply two large integers together.
LargeInt LargeInt::operator* (LargeInt& b){
    
    LargeInt c;
    LargeInt d, e;
    
    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int carry = 0;
    int total = 0;
    int zero = 0;
    
    int combo = negativeCheck(this->isNeg, b.isNeg);
    
    if(combo == 1){
        c.isNeg = false;
    }
    if(combo == 2 || combo == 3){
        c.isNeg = true;
    }
    
    auto itr = list1.begin();
    auto itr2 = b.list1.begin();
    
    
    while(count2 < b.list1.getLength()){
        carry = 0;
        
        while(count < list1.getLength()){
            total += carry + (*itr2 * *itr);
            if (total > 9)
            {
                carry = (total / 10);
                total = (total % 10);
                if(count3 == 0){
                    d.list1.insertFront(total);
                    total = 0;
                    if(count + 1 == list1.getLength() && size != 1)
                        d.list1.insertFront(carry);
                }
                else {
                    e.list1.insertFront(total);
                    total = 0;
                    if(count + 1 == list1.getLength() && size != 1)
                        e.list1.insertFront(carry);
                }
                if(b.size == 1 && size == 1){
                    d.list1.insertFront(carry);
                }
            }
            else {
                total += carry;
                if(count3 == 0){
                    d.list1.insertFront(total);
                    carry = 0;
                    total = 0;
                }
                else{
                    
                    e.list1.insertFront(total);
                    carry = 0;
                    total = 0;
                    
                }
            }
            count++;itr++;
        }
        count2++;itr2++;count3++; itr = list1.begin();count = 0;
    }
    for(int i = 0; i < 1; i++){
        e.list1.insertBack(0);
    }
    zero++;
    
    e.list1.reverse();
    if(b.list1.getLength() <= 2)
        d.list1.reverse();
    
    c.list1 = add(d,e);
    d.list1 = c.list1;
    d.list1.reverse();
    e.list1.destroyList();
    
    return c;
}


// Division operator to divide two large integers from each other
LargeInt LargeInt::operator/ (LargeInt& b){
    
    LargeInt c;
    
    int count = 0;
    int carry = 0;
    int total = 0;
    
    int res = negativeCheck(this->isNeg, b.isNeg);
    
    if(res == 1){
        c.isNeg = false;
    }
    if(res == 2 || res == 3){
        c.isNeg = true;
    }
    
    auto itr = list1.begin();
    auto itr2 = b.list1.begin();
    
    
    while (count < list1.getLength()){
        total = (carry + *itr) / *itr2;
        if(total % 2 == 1)
            carry = 10;
        else
            carry = 0;
        
        if(count + 1 == list1.getLength()){
            total = (carry + *itr) / *itr2;
            c.list1.insertFront(total);
            break;
        }
        
        c.list1.insertFront(total);
        count++; itr++;
        //total = 0;
    }
    
    return c;
}

// Modulus operator to attain modulus from two large integers
LargeInt LargeInt::operator% (LargeInt& b){
    
    LargeInt c;
    int total = 0;
    
    auto itr = list1.begin();
    auto itr2 = b.list1.begin();
    
    int count = *itr;
    total = *itr / *itr2;
    
    for (int i = 0; i < total; i++)
        count -= *itr2;
    
    c.list1.insertFront(count);
    
    return c;
}
