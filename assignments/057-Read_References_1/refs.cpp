#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

void swap(int& i1, int& i2)
{
          int temp = i1;	// copy i1’s value to temp
          i1 = i2;		// copy i2’s value to i1
          i2 = temp;		// copy i1’s old value to i2
}

void printv(std::vector<int> data) {
	std::cout << "data = {";
	for (int i=0; i < data.size(); i++) {
		std::cout << data[i];
		if (i+1 < data.size()) {
			std::cout << ", ";
		}
	}
	std::cout << "}\n";
}

int main()
{
	std::vector<int> data {10, 9, 8, 7, 6};
	printv(data);
	for (int i = 0; i < data.size(); i++) {
		std::cout << "i,data[i] = " << i << ", " << data[i] << "\n";
		if (data[i] > data[i+1] and i+i < data.size()) {
			swap(data[i],data[i+1]);
		}
	}
	printv(data);
}
