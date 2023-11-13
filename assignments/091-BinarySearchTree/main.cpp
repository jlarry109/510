#include "BinarySearchTree.hpp"
#include <vector>
#include <iostream>

int main() {
    BinarySearchTree<int> bst;

    std::vector<int> test = {5,3,7,2,4,6,8,9,10,11,15,17,16,14};

    for (auto i: test) {
        bst.insert(i);
    }

    std::cout << "Minimum value: " << bst.findMinimumValue() << "\n";

    // add testing/validation code as needed

    return EXIT_SUCCESS;
}
