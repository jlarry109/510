#include "IntegerLinkedList.hpp"
#include <iostream>
using std::cout;

int main() {
    // Place any test/validation code here
    IntegerLinkedList l1;
    IntegerLinkedList l2;
    IntegerLinkedList l3;
    l1 = l1.fromInt(2437);
    l2 = l2.fromString("8973");
    l3 = l3.fromString("8973");
    bool eq = l2 == l3;
    bool uneq = l1 != l2;
    std::cout << "l2 == l3: " << eq << std::endl;
    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
    std::cout << l3 << std::endl;
    std::cout << "l1 != l2 is: " << uneq << std::endl;
    l3 = l1;
    std::cout << l1 << std::endl;
    return EXIT_SUCCESS;
}
