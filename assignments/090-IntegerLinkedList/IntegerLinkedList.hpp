#ifndef __INT_LINKEDLIST__H__
#define __INT_LINKEDLIST__H__
#include <exception>
#include <stdexcept>
#include <ostream>
#include <string>
#include <iostream>
#include <limits>
class IntegerLinkedListNode {
    public:
    int data;    // stores the digit (0-9)
    IntegerLinkedListNode* next;

    IntegerLinkedListNode(int digit) : data(digit), next(nullptr) {
        if (digit < 0 || digit > 9) {
            throw std::invalid_argument("Digits must be in the range 0-9.");
        }
    }
};

class IntegerLinkedList {
private:
    IntegerLinkedListNode *head;
    
    void deallocateNodes();
    void copyNodes(IntegerLinkedListNode* currentRHS);

    void appendDigit(int digit) {
        IntegerLinkedListNode* newNode = new IntegerLinkedListNode(digit);

        if (!head) {
            head = newNode;
        } else {
            IntegerLinkedListNode* last = head;
            while (last->next) {
                last = last->next;
            }
            last->next = newNode;
        }
    }
    

public:
    IntegerLinkedList();
    ~IntegerLinkedList();

    IntegerLinkedList(const IntegerLinkedList &rhs);               // Copy Constructor
    IntegerLinkedList & operator=(const IntegerLinkedList &rhs);   // Copy Assignment Operator

    IntegerLinkedList(IntegerLinkedList &&rhs);                    // Move Constructor
    IntegerLinkedList & operator=(IntegerLinkedList &&rhs);        // Move Assignent Operator


    IntegerLinkedList operator+(const IntegerLinkedList & rhs);
    bool operator==(const IntegerLinkedList& rhs) const;
    bool operator!=(const IntegerLinkedList& rhs) const;

    static IntegerLinkedList fromString(const std::string& s); 
    static IntegerLinkedList fromInt(int i); 

    friend std::ostream & operator<<(std::ostream & s, const IntegerLinkedList & rhs);
};



#endif
