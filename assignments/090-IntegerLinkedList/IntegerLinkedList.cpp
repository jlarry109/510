#include "IntegerLinkedList.hpp"
#include <stdexcept>
#include <ostream>
#include <string>
#include <iostream>
#include <sstream>
IntegerLinkedList::IntegerLinkedList(): head(nullptr) {}

IntegerLinkedList::IntegerLinkedList(const IntegerLinkedList &rhs) : head(nullptr) {
    copyNodes(rhs.head);    
}

void IntegerLinkedList::copyNodes(IntegerLinkedListNode* currentRHS) {
    while (currentRHS != nullptr) {
        this->appendDigit(currentRHS->data);
        currentRHS = currentRHS->next;
    }
}

void IntegerLinkedList::deallocateNodes() {
      if (head == nullptr) {
      return;
    }
    IntegerLinkedListNode * node = head;
    while (node) {
      IntegerLinkedListNode * tmp = node->next;
      delete node;
      node = tmp;
    }
}


IntegerLinkedList & IntegerLinkedList::operator=(const IntegerLinkedList &rhs) {
    //Check for self-assignment first
    if (this != &rhs) {
        IntegerLinkedListNode * dummyNode = new IntegerLinkedListNode(0);
        IntegerLinkedListNode * ptrToDummyNode = dummyNode;
        IntegerLinkedList ans;
        IntegerLinkedListNode * iter = rhs.head;
        while (iter != nullptr) {
            dummyNode->next = new IntegerLinkedListNode(iter -> data);
            dummyNode = dummyNode->next;
            iter = iter->next; 
        }   
        deallocateNodes();
        head = ptrToDummyNode->next;
        delete ptrToDummyNode;

    }
    return *this;
}
IntegerLinkedList::IntegerLinkedList(IntegerLinkedList &&rhs): head(rhs.head) {
    rhs.head = nullptr;
}

IntegerLinkedList & IntegerLinkedList::operator=(IntegerLinkedList &&rhs){
    if (this != &rhs) { //Have to check for self-assignment

        deallocateNodes();
        head = rhs.head;
        rhs.head = nullptr;
    }
    return *this;
}



IntegerLinkedList::~IntegerLinkedList() {
     deallocateNodes();
}

IntegerLinkedList IntegerLinkedList::operator+(const IntegerLinkedList & rhs) {
    IntegerLinkedList res;
    IntegerLinkedListNode * ans = new IntegerLinkedListNode(0);
    IntegerLinkedListNode * ptrToDummyNode = ans;
    if(rhs.head == NULL) {
        res.head = ans;
        return res;
    }
  // Start with a remainder of 0
  int remainder = 0;
  IntegerLinkedListNode * l1 = this->head;
  IntegerLinkedListNode * l2 = rhs.head;
  // While we've not reached the end of l1 and l2,
  while (l1 != nullptr && l2 != nullptr) {
        // Sum = (l1->val + l2->val + remainder) mod 10, remainder = (l1->val + l2->val)/10
    int sum = (l1->data + l2->data + remainder) % 10;
    remainder = (l1->data + l2->data + remainder)/10;
    IntegerLinkedListNode * currNode = new IntegerLinkedListNode(sum);
    ans->next = currNode;
    ans = ans->next;
    l1 = l1->next;
    l2 = l2->next;
        // currNode = ListNode(sum)
  }
  //while  we haven't reached the end of l1,
  while (l1 != nullptr) {
      // Sum = (l1->val + remainder) mod 10, remainder = (l1->val)/10
    int sum = (l1->data + remainder) % 10;
    remainder = (l1->data + remainder)/10;
      // currNode = ListNode(sum)
    IntegerLinkedListNode * currNode = new IntegerLinkedListNode(sum);
    ans->next = currNode;
    ans = ans->next;
    l1 = l1->next;
  }
   //while  we haven't reached the end of l2,
  while (l2 != nullptr) {
      // Sum = (l2->val + remainder) mod 10, remainder = (l2->val)/10
    int sum = (l2->data + remainder) % 10;
    remainder = (l2->data + remainder)/10;
      // currNode = ListNode(sum)
    IntegerLinkedListNode * currNode = new IntegerLinkedListNode(sum);
    ans->next = currNode;
    ans = ans->next;
    l2 = l2->next;
  }
  // After processing every node in l1 and l2, If remainder != 0
  if (remainder > 0) {
     // Then create a node with val = remainder as the last node.
    IntegerLinkedListNode * currNode = new IntegerLinkedListNode (remainder);
    ans->next = currNode;
  }
  res.head = ptrToDummyNode->next;
  delete ptrToDummyNode;
  return res;
}


void toString (std::ostream & s, IntegerLinkedListNode * node) {
    if (node == nullptr) {
        return;
    }
    else {
        toString(s, node -> next);
        s << node -> data;
    }
}

std::ostream & operator<<(std::ostream & s, const IntegerLinkedList & rhs) {
    IntegerLinkedListNode * node = rhs.head;
    std::stringstream ss;
    toString(s, node);
    return s;
}


bool IntegerLinkedList::operator==(const IntegerLinkedList& rhs) const {
    IntegerLinkedListNode * lhsPtr = head;
    IntegerLinkedListNode * rhsPtr = rhs.head;
    while (lhsPtr != nullptr && rhsPtr != nullptr) {
        if (lhsPtr -> data != rhsPtr-> data) { 
            return false;
        }
        lhsPtr =  lhsPtr->next;
        rhsPtr = rhsPtr->next;
    }
    return (lhsPtr == nullptr && rhsPtr == nullptr); //If we got to the end of the list then the two lists were equal, otherwise, one list was shorter than the other (i.e. list not the same)
 }

bool IntegerLinkedList::operator!=(const IntegerLinkedList& rhs) const {
    return !(*this == rhs);
}

IntegerLinkedList IntegerLinkedList::fromString(const std::string & s) {
    
    IntegerLinkedList ans;
    for (size_t i = 0; i < s.length(); i++) {
        try {
            size_t pos;  // To store the position of the first non-numeric character
            std::string str = s.substr(s.length() - 1 - i, 1);
            int intValue = std::stoi(str, &pos);
            // Check if the entire string was converted (no non-numeric characters)
            if (pos != str.length()) {
                throw std::invalid_argument("Invalid argument - Non-numeric character detected");
            }
            ans.appendDigit(intValue);
        } catch (const std::invalid_argument& e) {
        // Handle the case when the conversion fails (e.g., non-numeric character)
        std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
        // Handle the case when the converted value is out of the range of int
        std::cerr << "Error: " << e.what() << std::endl;
    }
    }
    return ans;
}

IntegerLinkedList IntegerLinkedList::fromInt(int i) {
    IntegerLinkedListNode * dummyNode = new IntegerLinkedListNode(0);
    IntegerLinkedListNode * ptrToDummyNode = dummyNode;
    IntegerLinkedList ans;
    while (i) {
        int quotient = i / 10;
        int remainder = i % 10;
        dummyNode->next = new IntegerLinkedListNode(remainder);
        dummyNode = dummyNode->next;
        i = quotient;
    }
    ans.head = ptrToDummyNode->next;
    delete ptrToDummyNode;
    return ans;
}

/*std::ostream & operator<<(std::ostream & s, const IntegerLinkedList & rhs) {
    IntegerLinkedListNode * node = rhs.head;
    while (node) {
        s << node->data;
        node = node->next;
    }
}*/
