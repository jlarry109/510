#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>

template<typename T>
class Matrix {
 private:
  int numRows;          // Number of rows in the matrix
  int numColumns;       // Number of columns in the matrix
  std::vector<T> * rows; // Pointer to an array of vectors representing matrix rows

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = new std::vector<T>[numRows](); // Initialize an array of vectors, one for each row
    for (int i = 0; i < numRows; i++) {
      rows[i] = std::vector<T>(numColumns, T());  // Initialize each row with a vector of size numColumns
    }
  }

  explicit Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = new std::vector<T>[numRows](); // Create a new array of vectors for the copied matrix
    for (int i = 0; i < numRows; i++) {
      rows[i] = rhs.rows[i]; // Copy each row from the rhs matrix
    }
    return;
  }

  ~Matrix() { delete[] rows; } // Destructor to free memory allocated for rows

  Matrix & operator=(const Matrix & rhs) {
    if (*this == rhs) {
      return *this;
    }
    delete[] rows;   // Free memory for existing rows
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new std::vector<T>[numRows]();  // Create a new array of vectors for the assigned matrix
    for (int i = 0; i < numRows; i++) {
      rows[i] = rhs.rows[i]; // Copy each row from the rhs matrix
    }
    return *this;
  }

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows); // Ensure index is within bounds
    return rows[index];  // Return a const reference to the vector at the specified row
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows); // Ensure index is within bounds
    return rows[index];  // Return a const reference to the vector at the specified row
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;  // Matrices are not equal if the number of rows or columns differs
    }
    for (int i = 0; i < numRows; i++) {
      if (rows[i] != rhs.rows[i]) {
        return false;    // Matrices are not equal if any corresponding rows are not equal
      }
    }
    return true;    // Matrices are equal
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);   // Matrices must have the same dimensions for addition
    Matrix ans(numRows, numColumns);    // Create a new matrix for the result
    for (int i = 0; i < numRows; i++) {
      ans.rows[i] = rows[i] + rhs.rows[i];    // Element-wise addition of corresponding rows
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
    bool first = true;
    // Set the width and precision for formatting
    const int width = 7; // Total width for each element, including spaces
    const int precision = 4; // Number of digits after the decimal point

    // Enable fixed-point notation
    s << std::fixed;
    //s << '[';
    for (unsigned i = 0; i < rhs.size(); i++) {
        if (first) {
            first = false;
        }
        else {
            s << ",";
        }
        s << std::setw(width) << std::setprecision(precision) << rhs[i];
    }
    //s << ']';
    return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i < rhs.getRows() - 1) {
      s << std::endl;
      s << " ";
    }
  }
  s << "]";
  return s;
}

template<typename T>
std::vector<T> operator+(std::vector<T> & lhs, std::vector<T> & rhs) {
  assert(lhs.size() == rhs.size());   // Vectors must have the same size for addition
  std::vector<T> ans(lhs.size(), T());
  for (unsigned i = 0; i < lhs.size(); i++) {
    ans[i] = lhs[i] + rhs[i];   // Element-wise addition of corresponding elements
  }
  return ans;
}

#endif
