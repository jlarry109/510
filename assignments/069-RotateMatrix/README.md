# Rotate Matrix

For this assignment, you need to write a program that performs a 90 degree 
clockwise rotation of a 10x10 matrix.  (The dimensions are fixed so that you 
do not need to dynamically allocate the two-dimenisonal array  at runtime.  
Later assignments will require arbitrary sizes at runtime and the necessary 
knowledge will be presented in class prior to those assignments.)

To keep the input processing simple, the matrix will be a matrix of characters.
You can either use a c-style array such as 
```
char matrix[10][10]
```
or use the array class from the C++ STL
```
include <array>
std::array<std::array<char, 10>, 10> matrix
```
in your program.

The input will be read from a file whose name will be specified as a command line 
argument. Each line in the input file should contain 10 characters (plus a newline).

## Requirements
- Create a file called rotateMatrix.cpp
- Your program will take one command line argument, a string specifying the 
  input file to read.
- The input file should contain 10 lines, each of which have 10 (non-newline) characters
  (plus a newline).
- Your program should then rotate this 90 degrees clockwise, and print the result on stdout (cout).
- If there are any errors, your program should print an appropriate message to stderr (cerr), 
  and exit with EXIT_FAILURE.

**Notes**: 
- sample.txt provides sample input, and sample.out provides sample output.
- You may assume that we will only test with printable ASCII characters. 
- Line lengths and the total number of lines may not be correct in our tests.

**Hint**: This StackOverflow page describes the problem more in depth:
          https://stackoverflow.com/questions/42519/how-do-you-rotate-a-two-dimensional-array

Once you have tested your program locally (including validation checks), submit `rotateMatrix.cpp` to GradeScope for testing. 
