# Integer Matrix 
For this problem, you will write an `IntMatrix` class, making use of `IntArray` from the previous assignment.

First, copy your IntArray.cpp and IntArray.hpp from the previous assignment to this assignment folder.

As in the Integer Array assignment, four files have been provided:
- `IntMatrix.hpp`: provides the header (interface) of this class.  This file should not be modified. 
- `IntMatrix.cpp`: Contains the skeleton definitions (you need to implement these methods.)
- `test.cpp`: provides a main to test your array.  You should not need to modify this file.
- `Makefile`: will compile intMatrixTest to test your program.
- `intMatrixTest.txt`: output from executing intMatrixTest

Write the following members of IntMatrix:
  - `IntMatrix()`: A default constructor: it should initialize the matrix to have 0 rows and 0 columns.
  - `IntMatrix(int r, int c)`: A constructor that takes the number of rows and columns. 
     It should initialize the matrix to have the specified number of rows and columns.
  - `IntMatrix(const IntMatrix & rhs)`: A copy constructor, which makes a deep copy.
  - `~IntMatrix()`: A destructor, which frees any memory the Matrix has allocated.
  - `IntMatrix & operator=(const IntMatrix & rhs)`: An assignment operator, which makes a deep copy
  - `int getRows() const`: Returns the number of rows
  - `int getColumns() const`: Returns the number of columns
  - `IntArray & operator[](int index);` and

    `const IntArray & operator[](int index) const;`:
    - Check that the index (i.e., a row) is valid (i.e., in bounds). If not, throws an `out_of_range` exception
    - Returns a reference to the requested row.
  - `bool operator==(const IntMatrix & rhs) const`: Compares two matrices for equality. The matrices are equal if
      they have the same number of rows, the same number of columns,
      and each element is the same as the corresponding element in the
      other matrix. 
  - `IntMatrix operator+(const IntMatrix & rhs) const`;
     - validate that `this` and `rhs` have the same dimensions.  If not,
       through an `invalid_argument` exception.
     - Returns matrix (also the same dimensions as `this` and `rhs`) whose
      elements are the sum of the corresponding elements of `this`
      matrix and `rhs` (does matrix addition).

Additionally, write an overloading of the `<<` operator for
`std::ostream &` and `const IntMatrix &`:
  `std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs);`

- Prints (to s) a "[ ", followed by each row of the matrix
  (using IntArray's << operator). 
- These rows should be separated by ",\n".
- After the last row, you should print " ]" and return s. 

Compile, test, and valgrind your code. We have provided the output of 
the test program which the Makefile builds. You should create your own tests to validate intermediate versions of `IntMatrix`.

Submit `IntArray.cpp` and `IntMatrix.cpp` to the Gradescope assignment once you have validated your implementation of `IntMatrix`.