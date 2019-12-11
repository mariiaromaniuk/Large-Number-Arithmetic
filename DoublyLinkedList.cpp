//
//  DoublyLinkedList.cpp
//  Large Integer
//

#include "DoublyLinkedList.hpp"
#include <iostream>
using namespace std;


// Default constructor
template <class T>
DLinkedList<T>::DLinkedList(){
    head = NULL;
    tail = NULL;
    length = 0;
}

// Destructor
template <class T>
DLinkedList<T>::~DLinkedList(){
    Node<T>* p;
    while(head != NULL){
        p = head;
        head = head->next;
        delete p;
    }
    tail = NULL;
}

// Copy Constructor
template <class T>
DLinkedList<T>::DLinkedList(DLinkedList<T> &other){
    head = NULL;
    tail = NULL;
    copy(other);
}

// Copy Function
template <class T>
void DLinkedList<T>::copy(const DLinkedList<T> &other){
    if(other.head == NULL){
        head = tail = NULL;
        // return;
    } else {
        Node<T> *s = other.head;
        head = new Node<T>;
        head->data = s->data;
        Node<T> *p = head;
        
        while(s->next != NULL){
            p->next = new Node<T>;
            p = p->next;
            s = s->next;
            p->data = s->data;
            tail = p;
        }
        p->next = NULL;
    }
}

// Overloaded "=" operator
template <class T>
DLinkedList<T>& DLinkedList<T>::operator= (const DLinkedList<T> &other){
    if (this != &other){
        copy(other);
    }
    return *this;
}

// Checks if list is empty
template <class T>
bool DLinkedList<T>::isEmpty() const{
    return head == NULL;
}

// 2nd Destructor to call
template <class T>
void DLinkedList<T>::destroyList(){
    if (!isEmpty()){
        Node<T>* p = NULL;
        
        while (head){
            p = head;
            head = head->next;
            delete p;
        }
        head = tail = NULL;
        length = 0;
    }
}

// Remove item from the list
template <class T>
void DLinkedList<T>::deleteItem(T data){
    Node<T> *p, *prevP;
    
    if (!head) return;       // If null, do nothing
    
    if (head->data == data){ // If item is in the first node
        p = head;
        head = head->next;
        delete p;
        length--;
    } else {
        p = head;
    }
    while (p != NULL && p->data != data){
        prevP = p;
        p = p->next;
    }
    if (p){                  // If item in the rest of the list
        prevP->next = p->next;
        delete p;
        length--;
    }
    if (p == tail){
        tail = prevP;
    }
}

// Search the list for specific item
template <class T>
bool DLinkedList<T>::searchItem(T data){
    Node<T>* p = head;
    bool isFound = false;
    if(data == head->data || data == tail->data){
        isFound = true;
    } else {
        while (p != NULL && p->data != data){
            p = p->next;
        }
        if (p)
            isFound = true;
    }
    return isFound;
}

// Print list forward
template <class T>
void DLinkedList<T>::printForward() const{
    if (length > 0){
        Node<T>* p = head;
        while (p != NULL){
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    } else {
        cout << "List is empty " << endl;
    }
}

// Print list backward
template <class T>
void DLinkedList<T>::printBackward() const{
    if (length > 0){
        Node<T>* p = tail;
        
        while (p != NULL){
            cout << p->data << " ";
            p = p->prev;
        }
        cout << endl;
    } else {
        cout << "List is empty " << endl;
    }
}

// Add item to the front of the list
template <class T>
void DLinkedList<T>::insertFront(T data){
    Node<T>* p = new Node<T>;
    p->data = data;
    p->prev = NULL;
    
    if (length == 0){
        p->next = NULL;
        tail = p;
    } else {
        head->prev = p;
        p->next = head;
    }
    
    head = p;
    ++length;
}

// Add item to the end of the list
template <class T>
void DLinkedList<T>::insertBack(T data){
    Node<T>* p = new Node<T>;
    p->data = data;
    p->next = NULL;
    
    if (length == 0){
        p->prev = NULL;
        head = p;
    } else {
        tail->next = p;
        p->prev = tail;
    }
    
    tail = p;
    ++length;
}

// Replace one item with another
template <class T>
void DLinkedList<T>::replaceItem(T oldItem, T newItem){
    if (!isEmpty()){
        Node<T> *p = head;
        
        while (p != NULL){
            if (p->data == oldItem){
                p->data = newItem;
            }
            p = p->next;
        }
    }
}

//Set the length of the list
template <class T>
void DLinkedList <T>::setLength(int n){
    length = n;
}

// Get the length of the list
template <class T>
int DLinkedList<T>::getLength() const{
    return length;
}

// Delete last item of the list
template <class T>
void DLinkedList<T>::deleteLast(){
    
    Node<T>* s = NULL;
    Node<T>* p = NULL;
    p = head;
    
    if (!head){
        return;
    }
    if (head->next == NULL){
        head = head->next;
        delete p;
        tail = head;
    } else {
        while(p != NULL && p != tail){
            s = p;
            p = p->next;
        }
        if (p){
            s->next = p->next;
            delete p;
            tail = s;
        }
    }
}

template <class T>  // Reverse list
void DLinkedList<T>::reverse(){
    Node<T>* temp = head;
    Node<T>* p = head;
    head = tail;
    tail = temp;
    
    while (p!= NULL){
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;
        p = p->next;
    }
}

template class DLinkedList<int>;

