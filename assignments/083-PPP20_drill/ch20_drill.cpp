#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <cassert>
#include <cstdlib>

template<typename Iter1>
void print(Iter1 start, Iter1 end, const std::string & containerType) { 
    std::cout << containerType << ": {";
    while (start != end) {
        std::cout << *start;
        ++start;
        if (start != end) {
            std::cout << ", ";
        }
    }
    std::cout << "}";
    std::cout << std::endl;
}


template<typename Iter1, typename Iter2>
Iter2 copy2(Iter1 f1, Iter1 e1, Iter2 f2) {
    //assert(std::distance(f1, e1) == std::distance(f2, f2 + std::distance(f1, e1)));
    /*while (std::distance(f1, e1) > 0 && std::distance(f2, f2 + std::distance(f1, e1)) > 0) {
        *f2 = *f1;  // Copy element
        ++f1;
        ++f2;
    }*/
    std::copy(f1, e1, f2);
    return f2;  // Return iterator pointing to the position after the last copied element
}

template <typename T, typename G>
void increment (typename T::iterator start, typename T::iterator end, G value) { 
    //Having G different to T allows the increment function to be operational so long
    //as + is defined or overloaded for types T and G. Note: T and G may be the same type
    while (std::distance(start, end) > 0/*start < end*/) {
        (*start)+= value;
        std::advance(start, 1);
    }
}

template <typename Iter1, typename G>
void increment(Iter1 start, Iter1 end, G value) {
    while (start < end) {
        (*start)+= value;
        std::advance(start, 1);
    }
}

template <typename T, typename G>
void increment (T arr [], size_t arrSize, G value) {
    for (size_t i = 0; i < arrSize; i++) {
        arr[i] += value;
    }
}

int main () {
    int arr [] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    std::vector<int> vec = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::list<int> lst = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    //increment(arr, 10, 2);
    increment<int* >(std::begin(arr), std::end(arr), 2);
    increment<std::vector<int> >(vec.begin(), vec.end(), 3);
    increment<std::list<int> > (lst.begin(),lst.end(), 5);
    //print<int *>(std::begin(arr), std::end(arr));
    //print(vec.begin(), vec.end());
    //print(lst.begin(), lst.end());
    std::vector<int>::iterator it = copy2(std::begin(arr), std::end(arr), vec.begin());
    auto iter = copy2(lst.begin(), lst.end(), std::begin(arr));
    print<int *>(iter, std::end(arr), "array");
    print(it, vec.end(), "vector"); 
    print(lst.begin(), lst.end(), "list");
    return EXIT_SUCCESS;
}
