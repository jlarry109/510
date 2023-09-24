# Hello C++

Your goal in this assignment is to compile and run the provided C++ program in your development environment. 

"
The only way to learn a new programming language is by writing programs in it. 
The first program is the same for all languages: Print the words 'hello, world' 

This is the big hurdle; to leap over it you have to be able to create the program text somewhere,
compile it successfully, load it, run it, and find out where your output went.
"
- 'The C Programming Language', Kernigan and Ritchie

We've provided the necessary header file, 'std_lib_facilities.h' 
You need to create a file, hello.cpp, containing the following C++ code (Stroustrup PPP, Ch 2.1):
```
#include "std_lib_facilities.h"

int main()             // C++ programs start by executing the function main
{
          cout << "Hello, World!\n"; // output "Hello, World!"
          return 0;
}
```

To compile:
1. open a terminal window (Terminal -> new window in VS Code menu)
2. change to the assignment directory in the terminal window
   pwd - displays/prints the current(present) working directory
   ls - lists the files in that directory
   cd <directoryName>  - changes to that directory
   cd .. - changes to the parent directory
3. To compile hello.cpp: g++ -std=c++17 hello.cpp

Once you have succeeded in creating, compiling, and running the code in your environment, submit the code in the 'hello_cpp' Gradescope assignment for credit.

