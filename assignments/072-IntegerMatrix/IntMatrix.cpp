#include "IntMatrix.hpp"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(NULL) {
  rows = new IntArray *[r];
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(NULL) {
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;

    rows = new IntArray *[numRows];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new IntArray(*rhs.rows[i]);
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  if(!(0 <= index && index < numRows)) {
        std::cerr << "expected(row indexing) - Out of Range error: Index is out of range" << std::endl;
        throw std::out_of_range("Index is out of range");
    }
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  if(!(0 <= index && index < numRows)) {
        std::cerr << "expected(row indexing) - Out of Range error: Index is out of range" << std::endl;
        throw std::out_of_range("Index is out of range");
    }
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  if(!(numRows == rhs.numRows && numColumns == rhs.numColumns)) {
    throw std::invalid_argument("Dimension of operands must be equal");
  }
  IntMatrix newMatrix = IntMatrix(*this);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      newMatrix[i][j] += rhs[i][j];
    }
  }
  return newMatrix;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  int length = rhs.getRows();
  for (int i = 0; i < length; i++) {
    s << rhs[i];
    if (i < length - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
