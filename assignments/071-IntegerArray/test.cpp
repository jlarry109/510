#include <iostream>
#include <random>
#include "IntArray.hpp"

std::mt19937 eng(1842);    // Create a Mersenne Twister seeded with 1842

size_t produceRandomNumber(size_t max) {
    std::uniform_int_distribution<> distr(0, max-1);  
    return distr(eng);
}

int maxIndex(const IntArray & array) {
  if (array.size() == 0) {
    return -1;
  }
  int answer = 0;
  for (int i = 1; i < array.size(); i++) {
    if (array[i] > array[answer]) {
      answer = i;
    }
  }
  return answer;
}

void randomize(IntArray & array) {
  for (int i = 0; i < array.size(); i++) {
    int temp(array[i]);
    int swapInd = produceRandomNumber(array.size());
    array[i] = array[swapInd];
    array[swapInd] = temp;
  }
}

void randomizeAndPrint(IntArray & array) {
  randomize(array);
  std::cout << array << std::endl;
  std::cout << "Largest element at index " << maxIndex(array) << std::endl;

}

int main(void) {
  IntArray intArray(10);
  for (int i  = 0; i < intArray.size(); i++) {
    intArray[i] = i*i;
  }
  IntArray intArray2(intArray);
  
  if (intArray == intArray2) {
    std::cout << "The two int arrays are the same\n";
  }
  else {
    std::cout << "The two int arrays are different\n";
  }

  randomizeAndPrint(intArray);

  std::cout << "intArray2 is " << intArray2 << std::endl;
  if (intArray == intArray2) {
    std::cout << "The two int arrays are the same\n";
  }
  else {
    std::cout << "The two int arrays are different\n";
  }

  intArray2 = intArray;
  std::cout << "Now intArray2 is "<< intArray2 << std::endl;
  if (intArray != intArray2) {
    std::cout << "The two int arrays are different\n";

  }
  else {
    std::cout << "The two int arrays are the same\n";
  }

  return EXIT_SUCCESS;
}
