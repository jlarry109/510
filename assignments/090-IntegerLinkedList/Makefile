test: main.cpp IntegerLinkedList.o
	g++ -o test -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 main.cpp IntegerLinkedList.o 

IntegerLinkedList.o: IntegerLinkedList.hpp IntegerLinkedList.cpp
	g++ -c -o IntegerLinkedList.o -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 IntegerLinkedList.cpp

clean:
	rm -rf *.dSYM *.o test
