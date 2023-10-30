CPPFLAGS=-Wall -pedantic -std=c++17 -Werror -ggdb3

compile: rootmat_cpp squaremat_cpp

rootmat_cpp: rootmat.cpp
	g++  -o rootmat $(CPPFLAGS) rootmat.cpp

squaremat_cpp: squaremat.cpp
	g++  -o squaremat $(CPPFLAGS) squaremat.cpp

clean:
	rm -rf *.o *.dSYM rootmat squaremat
