//
//  DoublyLinkedList.hpp
//  Large Integer
//

#ifndef DoublyLinkedList_hpp
#define DoublyLinkedList_hpp

#include <stdio.h>
#include <iostream>


template <class T>
struct Node {
    T data;
    // Pointing to the next node
    Node<T>* next;
    // Pointing to the previous node
    Node<T>* prev;
};

template <class T>
class DLinkedList {
    
public:
    // Default Constructor
    DLinkedList();
    // Copy Constructor
    DLinkedList(DLinkedList<T> & other);
    // Destructor
    ~DLinkedList();
    
    class Iterator {
        // Iterator class
        friend class DLinkedList;
        Iterator(Node<T> *newPtr) : current(newPtr) {}
        
    public:
        // Iterator constructor
        Iterator() : current(NULL) {}
        
        // Iterator increment
        Iterator operator++(T data) {
            Iterator temp = *this;
            current = current->next;
            return temp;
        }
        
        // Iterator decrement
        Iterator operator --(T data) {
            Iterator temp = *this;
            current = current->prev;
            return temp;
        }
        
        // Iterator "==" operator
        bool operator ==(const Iterator &itr) const {
            return current == itr.current;
        }
        // Iterator "!=" operator
        bool operator !=(const Iterator &itr) const {
            return current != itr.current;
        }
        
        // Iterator "*" operator
        T& operator *() const {
            return current->data;
        }
        
    private:
        Node<T>* current;
    };
    
    // Return a pointer that points to the beginning of the list
    Iterator begin() const{
        return Iterator(head);
    }
    // Return a pointer that points to the end of the list
    Iterator end() const{
        return Iterator(NULL);
    }
    
    // Copy Function
    void copy(const DLinkedList<T> &other);
    
    // Overloaded "=" operator
    DLinkedList<T>& operator=(const DLinkedList<T> &other);
    
    // Checks if list is empty
    bool isEmpty() const;
    
    // 2nd Destructor to call
    void destroyList();
    
    // Remove item from the list
    void deleteItem(T data);
    
    // Search the list for specific item
    bool searchItem(T data);
    
    // Print the data of the list forward
    void printForward() const;
    
    // Print the data of the list backward
    void printBackward() const;
    
    // Add item to the front of the list
    void insertFront(T data);
    
    // Add item to the end of the list
    void insertBack(T data);
    
    // Replace one item with another
    void replaceItem(T oldItem, T newItem);
    
    // Set the length of the list
    void setLength(int n);
    
    // Get the length of the list
    int getLength() const;
    
    // Delete last item of the list
    void deleteLast();
    
    // Reverse order
    void reverse();
    
    
protected:
    // First Node of the list
    Node<T>* head;
    // Last Node of the list
    Node<T>* tail;
    // Size of the list
    int length;
    
};

#endif /* DoublyLinkedList_hpp */
