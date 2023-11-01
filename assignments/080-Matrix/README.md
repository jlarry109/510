# Matrix

Associated with _Programming: Principles and Practices Using C++_, the 
author provides a Matrix library that allows developers to create 
numerical-based applications. The distribution for this assignment 
contains this library in the files Matrix.h and MatrixIO.h.

You should read sections 24.3, 24.4, and 24.5 in the textbook.

Using the provided Matrix library, you will need to write two programs:
1. `squaremat.cpp` that squares each element of a two-dimensional matrix.
2. `rootmat.cpp` that computes the square root of each element of a two-dimensional matrix.

Both programs read their input from standard input (i.e., `cin`) and write their output
to standard output (i.e., `cout`).

One way you can test your programs, is to "pipe" the results of one program into the second.
The result should be the original input matrix.
```
./rootmat < example.txt | ./squaremat 
```

The input format specifies the number of rows and columns as the first two numbers. 
Then, it has a `{` to mark the start of the matrix.
Each row in the matrix is represented by `{` numbers `}` where numbers is a space-separated 
list of doubles. The number of doubles equals the number of columns.
Finally, it has a `}` to mark the end of the matrix. See below for an example.

Notes:
- We have provided three input files: 1x1.txt, 2x2.txt, and 10x20.txt
- Each associated output either has a .root or a .square suffix.
- Use `double` as the type.
- Use the `apply` function to modify the matrix. You should not need to write your
  own code to iterate over the matrix.
- Use the provided functionality in MatrixIO.h to read and write the data using the
  `>>` and `<<` operators.
- `cmath` provides the `sqrt()` function.

Example input, saved as 2x2.txt:
```
2 2
{
{ 1, 2 }
{ 3, 4 } 
}
```

Example run: 
```
./squaremat < exa2x2mple1.txt
2 2
{
{ 1, 4 }
{ 9, 16 } 
}
```
Example run: 
```
./squaremat.exe < 2x2.txt | ./rootmat.exe
2 2
{
{ 1, 2 }
{ 3, 4 } 
}
```

Once you have validated your programs, submit `rootmat.cpp` and `squaremat.cpp` to the Gradescope assignment.