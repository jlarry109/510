#ifndef SOLVER_H
#define SOLVER_H

#include "MatrixIO.h"
using namespace std;
using namespace Numeric_lib;
using Numeric_lib::Index;

typedef Numeric_lib::Matrix<double, 2> Matrix2D;
typedef Numeric_lib::Matrix<double, 1> Vector1;

//------------------------------------------------------------------------------

void classical_elimination(Matrix2D& A, Vector1& b);


//------------------------------------------------------------------------------

Vector1 back_substitution(const Matrix2D& A, const Vector1& b);

// An exception of this type is thrown when elimination fails.
struct Elim_failure : std::domain_error {
    Elim_failure(string s) : std::domain_error(s) { }
};


//------------------------------------------------------------------------------

// An exception of this type is thrown when back substitution fails.
struct Back_subst_failure : std::domain_error {
    Back_subst_failure(string s) : std::domain_error(s) { }
};


// YOUR CODE GOES HERE...
#endif
