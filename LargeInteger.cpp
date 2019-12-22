//
//  LargeInteger.cpp
//  Large Integer
//
//  Created by Mariia Romaniuk
//


#include "LargeInteger.hpp"


// Overloaded operator << prints out an array of an object backwards
ostream& operator << (ostream& out, LargeInt &other){
    other.list.setIteratorLast();
    
    while (!other.list.didIteratorFinish()){
        out << other.list.getIteratorInfo();
        other.list.setIteratorPrev();
    }
    return out;
}


// Overloaded operator >> first takes in input as a string
// whose length determines the length of an array
istream& operator >> (istream& in, LargeInt &other){
    // Takes a string as input
    string str;
    in >> str;
    int item;
    
    for (int i = 0; i != str.length(); i++){
        item = (str.at(i) - '0');
        other.list.insertItemFront(item);
    }
    return in;
}


// Default constructor
LargeInt::LargeInt(){
}


// Destructor
LargeInt::~LargeInt(){
}


// Overloaded addition operator returns an object of LargeInt
LargeInt LargeInt::operator + (LargeInt other){
    LargeInt temp;
    temp.list.initializeList();
    int smallerL;
    int sumLength;
    
    if (list.getLength() > other.list.getLength()){
        sumLength = list.getLength();
        smallerL = other.list.getLength();
    }
    else {
        sumLength = other.list.getLength();
        smallerL = list.getLength();
    }
    
    temp.list.setLength(sumLength);
    int s = 0;
    
    list.setIteratorFirst();
    other.list.setIteratorFirst();
    
    for (int i = 0; i < sumLength; i++){
        if (i < smallerL){
            s += list.getIteratorInfo() + other.list.getIteratorInfo();
            if(!list.didIteratorFinish())
                list.setIteratorNext();
            if(!other.list.didIteratorFinish())
                other.list.setIteratorNext();
        }
        else {
            if (sumLength == list.getLength()){
                s += list.getIteratorInfo();
                if (!list.didIteratorFinish())
                    list.setIteratorNext();
            }
            else {
                s += other.list.getIteratorInfo();
                if (!other.list.didIteratorFinish())
                    other.list.setIteratorNext();
            }
        }
        
        if (s > 9){
            s = s -10;
            temp.list.insertItemBack(s);
            s = 1;
        }
        else {
            temp.list.insertItemBack(s);
            s = 0;
        }
    }
    
    if (s == 1){
        temp.list.insertItemBack(1);
        temp.list.setLength(sumLength + 1);
    }
    return temp;
}


// Overloaded substruction operator
LargeInt LargeInt::operator - (LargeInt other){
    LargeInt temp;
    temp.list.initializeList();
    
    int sumLength = list.getLength() >= other.list.getLength() ? list.getLength() : other.list.getLength();
    
    temp.list.setLength(sumLength);
    
    int sign = 1;;
    
    if (((*this).isNegative() && !other.isNegative()) || (!(*this).isNegative() && other.isNegative())){
        sign = -1;
    }
    else
        sign = 1;
    
    int s = 0;
    int carry = 0;
    int num1 = 0;
    int num2 = 0;
    bool otherBigger = false;
    
    if (other > *this)
        otherBigger = true;
    
    if (*this == other)
        temp.list.insertItemFront(0);
    else {
        list.setIteratorFirst();
        other.list.setIteratorFirst();
        
        for (int i = 0; i < sumLength; i++){
            if (!list.didIteratorFinish()){
                num1 = list.getIteratorInfo();
                list.setIteratorNext();
            }
            
            if (!other.list.didIteratorFinish()){
                num2 = other.list.getIteratorInfo();
                other.list.setIteratorNext();
            }
            
            if (!otherBigger){
                s = num1 - (num2 + carry);
                if (s < 0){
                    s = (num1 + 10) - (num2 + carry);
                    carry = 1;
                }
                else
                    carry = 0;
            }
            
            if (otherBigger){
                s = num2 - (num1 + carry);
                
                if (s < 0){
                    s = (num2 + 10) - (num1 + carry);
                    carry = 1;
                }
                else
                    carry = 0;
            }
            
            if (otherBigger && i == sumLength-1){
                temp.list.insertItemBack(s*(-1));
            }
            else {
                if (s == 0 && list.didIteratorFinish()){
                }
                else {
                    temp.list.insertItemBack(s);
                }
            }
            num1 = 0;
            num2 = 0;
            
            if (s == 0 && other.list.didIteratorFinish() && otherBigger){
                temp.list.deleteLast();
                temp.list.setIteratorLast();
                s = temp.list.getIteratorInfo();
                temp.list.deleteLast();
                temp.list.setIteratorLast();
                temp.list.insertItemBack(s * -1);
            }
        }
    }
    if (carry > 0)
        temp.list.insertItemBack(carry);
    
    return temp;
}


// Helper function for overloaded multiplication operator
LargeInt LargeInt::multiply(LargeInt value, const int num){
    LargeInt temp2;
    int carry = 0;
    
    for (value.list.setIteratorFirst(); !value.list.didIteratorFinish(); value.list.setIteratorNext()){
        int sum = num*value.list.getIteratorInfo() + carry;
        carry = sum / 10;
        sum %= 10;
        temp2.list.insertItemBack(sum);
    }
    
    if (carry > 0)
        temp2.list.insertItemBack(carry);
    
    return temp2;
}


// Overloaded multiplication operator
LargeInt LargeInt::operator * (LargeInt other){
    LargeInt product,temp;
    int count = 0;
    int power = 0;
    
    product = *this;
    
    for (other.list.setIteratorFirst(); !other.list.didIteratorFinish();other.list.setIteratorNext()){
        temp = (multiply(*this, other.list.getIteratorInfo()));
        
        power = count;
        if (power > 0){
            while (power != 0){
                temp.list.insertItemFront(0);
                power--;
            }
        }
        count++;
        
        if (count == 1)
            product = temp;
        else
            product = product + temp;
    }
    return product;
}


// Overloaded division operator
LargeInt LargeInt::operator / (LargeInt other){
    LargeInt temp,temp1;
    
    list.setIteratorLast();
    if (other>*this)
        temp1.list.insertItemBack(0);
    
    else {
        while (!list.didIteratorFinish()){
            temp.list.insertItemFront(list.getIteratorInfo());
            if (temp > other || temp == other) {
                int count = 0;
                while (temp == other || temp > other) {
                    temp = temp - other;
                    count++;
                }
                temp1.list.insertItemFront(count);
            }
            list.setIteratorPrev();
        }
    }
    return temp1;
}


// Overloaded modulus operator
LargeInt LargeInt::operator % (LargeInt other){
    while (*this > other || *this == other){
        *this = *this - other;
    }
    return *this;
}


// Overloaded assignment operator
LargeInt LargeInt::operator = (LargeInt other){
    if (this != &other){
        list.initializeList();
        
        other.list.setIteratorFirst();
        
        while (!other.list.didIteratorFinish()){
            list.insertItemBack(other.list.getIteratorInfo());
            other.list.setIteratorNext();
        }
        return *this;
    }
    else {
        cout << "\nparameter is the same as the calling object: ";
        return other;
    }
}


// Overloaded operator equal
bool LargeInt::operator == (LargeInt other){
    if (list.getLength() == other.list.getLength()){
        list.setIteratorFirst();
        other.list.setIteratorFirst();
        
        while (!list.didIteratorFinish()){
            if (list.getIteratorInfo() != other.list.getIteratorInfo())
                return false;
            list.setIteratorNext();
            other.list.setIteratorNext();
        }
        return true;
    }
    else
        return false;
}


// Overload the "greater than or equal to" operator
bool LargeInt::operator >= (LargeInt other){
    bool isTrue = false;
    
    if (*this > other || *this == other)
        isTrue = true;
    
    return isTrue;
}


// Overload the "less than or equal to" operator
bool LargeInt::operator <= (LargeInt other){
    bool isTrue = false;
    
    if (*this < other || *this == other)
        isTrue = true;
    
    return isTrue;
}


// Overloaded "less then" operator
bool LargeInt::operator < (LargeInt other){
    if (list.getLength() > other.list.getLength())
        return false;
    else {
        if (list.getLength() < other.list.getLength())
            return true;
        else {
            list.setIteratorLast();
            other.list.setIteratorLast();
            
            if (list.getIteratorInfo() < other.list.getIteratorInfo())
                return true;
            else
                return false;
        }
    }
}


// Overloaded "greater then" operator
bool LargeInt::operator > (LargeInt other){
    if (list.getLength() < other.list.getLength())
        return false;
    else {
        if (list.getLength() > other.list.getLength())
            return true;
        else{
            list.setIteratorLast();
            other.list.setIteratorLast();
            
            if (list.getIteratorInfo() > other.list.getIteratorInfo())
                return true;
            else
                return false;
        }
    }
}


// Check if number has a negative sign
bool LargeInt::isNegative(){
    list.setIteratorLast();
    return (list.getIteratorInfo() < 0)? true:false;
}
