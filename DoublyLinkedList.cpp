//
//  DoublyLinkedList.cpp
//  Large Integer
//
//  Created by Mariia Romaniuk
//


#include "DoublyLinkedList.hpp"


// Overloaded operator <<
template <class Type>
ostream& operator << (ostream& out, const DoublyLinkedList<Type> &other){
    Node<Type> *current = other.first;
    while (current != NULL){
        out << current->info << ' ';
        current = current->next;
    }
    return out;
}


// Overloaded operator >>
template <class Type>
istream& operator >> (istream& in, DoublyLinkedList<Type> &other){
    string str;
    in >> str[0];
    return in;
}


// Constructor
template <class Type>
DoublyLinkedList<Type>::DoublyLinkedList(){
    first = NULL;
    last = NULL;
    iterator = NULL;
    length = 0;
}


// Destructor
template <class Type>
DoublyLinkedList <Type>::~DoublyLinkedList(){
    Node<Type> *current;
    while (first != NULL){
        current = first;
        first = first->next;
        delete current;
    }
}


// Copy constructor
template <class Type>
DoublyLinkedList<Type>::DoublyLinkedList(const DoublyLinkedList<Type> &other){
    max = other.max;
    length = other.length;
    
    first = new Node<Type>;
    Node<Type> *q = other.first;
    Node<Type> *p = first;
    
    while (q != NULL){
        p->info = q->info;
        q = q->next;
        
        if (q != NULL){
            p->next = new Node<Type>;
            p = p->next;
        }
        else {
            p->next = NULL;
            last = p;
        }
    }
}


// Overloaded assignment operator
template <class Type>
DoublyLinkedList<Type> DoublyLinkedList<Type>::operator = (const DoublyLinkedList<Type> &other){
    if (this != &other){
        if (other.isEmpty()){
            first = last = NULL;
            length = 0;
            max = 100;
        }
        else {
            first = new Node<Type>;
            Node<Type> *p;
            p = first;
            Node<Type> *q = other.first;
        }
    }
}


// List initialization function
template <class Type>
void DoublyLinkedList<Type>::initializeList(){
    first = NULL;
    last = NULL;
    iterator = NULL;
    length = 0;
}


// Function to check if list is empty
template <class Type>
bool DoublyLinkedList<Type>::isEmpty(){
    return (first == NULL);
}


// Get length of the list
template <class Type>
int DoublyLinkedList<Type>::getLength(){
    return length;
}


// Set length of the list
template <class Type>
void DoublyLinkedList<Type>::setLength(int n){
    length = n;
}


// Insert item to the front of the list
template <class Type>
void DoublyLinkedList<Type>::insertItemFront(const Type &item){
    Node<Type> *newNode;
    newNode = new Node<Type>;
    newNode->info = item;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (first == NULL){
        first = last = newNode;
        first->prev = NULL;
        first->next = NULL;
    }
    else {
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    }
    length++;
}


// Insert item to the back of the list
template <class Type>
void DoublyLinkedList<Type>::insertItemBack(const Type &item){
    Node<Type> *newNode;
    newNode = new Node<Type>;
    newNode->info = item;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (first == NULL)
        first = last = newNode;
    else {
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }
    length++;
}


// Function to print list forward
template <class Type>
void DoublyLinkedList <Type>::printForward(){
    Node<Type> *current;
    current = first;
    
    while(current != NULL){
        cout << current->info << ' ';
        current = current->next;
    }
}


// Function to print list backward
template <class Type>
void DoublyLinkedList<Type>::printBackward(){
    Node<Type> *current;
    current = last;
    
    while (current != NULL){
        cout << current->info << ' ';
        current = current->back;
    }
}


// Dummy function to pass the first to printForwardRec
template <class Type>
void DoublyLinkedList<Type>::printForwardCallRec(){
    printForwardRec(first);
}


// Function to print list forward recursively
template <class Type>
void DoublyLinkedList<Type>::printForwardRec(Node<Type> *p){
    if (p != NULL){
        cout << p->info << ' ';
        printForwardRec(p->next);
    }
}


// Dummy function to pass the first to printBackwardRec
template <class Type>
void DoublyLinkedList<Type>::printBackwardCallRec(){
    printBackwardRec(first);
}


// Function to print list backward recursively
template <class Type>
void DoublyLinkedList<Type>::printBackwardRec(Node<Type> *p){
    if (p != NULL){
        printBackwardRec(p->next);
        cout << p->info << ' ';
    }
}


// Deletes first item in the list
template <class Type>
void DoublyLinkedList<Type>::deleteFirst(){
    if (!isEmpty()){
        Node<Type> *current = first;
        first = first->next;
        delete current;
    }
}


// Deletes last item in the list
template <class Type>
void DoublyLinkedList<Type>::deleteLast(){
    if (!isEmpty()){
        if (first == last){
            delete first;
            first = last = NULL;
        }
        else {
            Node<Type> *temp = last;
            last = last->prev;
            last->next = NULL;
            delete temp;
        }
        length--;
    }
}


// Function that returns number of itemes in the list
template <class Type>
int DoublyLinkedList<Type>::getNumOfItem(Type item){
    if (!isEmpty()){
        Node<Type> *current = first;
        int count = 0;
        
        while (current != NULL){
            if (current->info == item)
                count++;
            
            current = current->next;
        }
        return count;
    }
    return 0;
}


// Function that replaces one item with another one
template <class Type>
void DoublyLinkedList<Type>::replaceItem(Type oldItem, Type newItem){
    if (!isEmpty()){
        Node<Type> *current = first;
        
        while (current != NULL){
            if (current->info == oldItem)
                current->info = newItem;
            
            current = current->next;
        }
    }
}


// Dummy function to pass the first to replaceItemRec
template <class Type>
void DoublyLinkedList<Type>::replaceItemCallRec(Type oldItem, Type newItem){
    if (!isEmpty())
        replaceItemRec(oldItem, newItem, first);
}


// Function that replaces one item with another one recursively
template <class Type>
void DoublyLinkedList<Type>::replaceItemRec(Type oldItem, Type newItem, Node<Type> *&current){
    if (current != NULL){
        if (current->info == oldItem)
            current->info = newItem;
        
        replaceItemRec(oldItem, newItem, current->next);
    }
}


// Function to check if current next is a null pointer
template <class Type>
bool DoublyLinkedList<Type>::isNextNull(){
    if (iterator->next == NULL)
        return true;
    else
        return false;
}


// Set iterator to the first item of the list
template <class Type>
void DoublyLinkedList<Type>::setIteratorFirst(){
    iterator = first;
}


// Set iterator to the last item of the list
template <class Type>
void DoublyLinkedList<Type>::setIteratorLast(){
    iterator = last;
}


// Set iterator to the next node
template <class Type>
void DoublyLinkedList<Type>::setIteratorNext(){
    iterator = iterator->next;
}


// Set iterator to the previous node
template <class Type>
void DoublyLinkedList<Type>::setIteratorPrev(){
    iterator = iterator->prev;
}


// Check if iterator finished traversing the list
template <class Type>
bool DoublyLinkedList<Type>::didIteratorFinish(){
    return (iterator == NULL);
}


// Get the data from the current node
template <class Type>
Type DoublyLinkedList<Type>::getIteratorInfo(){
    return iterator->info;
}
