#include "IntegerLinkedList.hpp"


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
}


IntegerLinkedList & IntegerLinkedList::operator=(const IntegerLinkedList &rhs) {
    deallocateNodes();
    copyNodes(rhs.head);
    return *this;
}

IntegerLinkedList::IntegerLinkedList(IntegerLinkedList &&rhs): head(rhs.head) {
    rhs.head = nullptr;
}

IntegerLinkedList & IntegerLinkedList::operator=(IntegerLinkedList &&rhs){
    deallocateNodes();
    head = rhs.head;
    rhs.head = nullptr;

    return *this;
}



IntegerLinkedList::~IntegerLinkedList() {
     deallocateNodes();
}

IntegerLinkedList IntegerLinkedList::operator+(const IntegerLinkedList & rhs) {

}


bool IntegerLinkedList::operator==(const IntegerLinkedList& rhs) const {

}

bool IntegerLinkedList::operator!=(const IntegerLinkedList& rhs) const {
}

IntegerLinkedList IntegerLinkedList::fromString(const std::string& s) {
}

IntegerLinkedList IntegerLinkedList::fromInt(int i) {
}



std::ostream & operator<<(std::ostream & s, const IntegerLinkedList & rhs) {
}