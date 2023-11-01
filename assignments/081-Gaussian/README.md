# Gaussian Elimination: Solving systems of linear equations.

In PPP Chapter 24.6.1-3, the textbook presents code for solving linear equations using Gaussian elimination. 
 
Your task is to use the chapter's code to implement a solver (function 'classical_gaussian_elimination') 
that takes a matrix A and a vector B, solves the system, and returns the solution vector.

Your code should be added to the provided header file, solver.hpp.

We've included a starter solver.hpp, a driver program, main.cpp, example data files, and a Makefile.

## Driver program

The driver program, gaussian, reads in files containing A and B, and solves and prints the output.
You should not need to change the Makefile or main.cpp.

Usage: ./gaussian A.txt B.txt 

Note: The input files use the same input format as matrix_cpp, e.g. a 2-D matrix with the number of rows and columns in the first line.

## Example: 

For example, consider the following system of equations:
```
2x + 3y = 6
 x -  y = 1/2
```

translates to the following A matrix (in file A1.txt):
```
2 2
{
{2 3}
{1 -1}
}
```

and the following B vector (in file B1.txt):
```
1 2
{ { 6 .5 } }
```

running './gaussian EA1.txt EB1.txt' should yield:
```
1 2
{ {1.5 1} }
```

## Suggested steps: 
a. In solver.hpp, implement the code from PPP section 26.4.1 for classical_gaussian_elimination()
b. Test your solver with the example given above, stored in A1.txt and B1.txt.
c. Test your solver with A2.txt and B2.txt and observe that it throws 'Elimination failure in row 0'
d. Update 'classical_gaussian_elimination' to use 'elim_with_partial_pivot' rather than 'classical_elimination'
e. Test again with A2.txt and B2.txt and observe that it now finds a solution.

Once your code is complete and verified, submit your updated `solver.hpp` 
to the Gradescope assignment.
