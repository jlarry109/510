
#ifndef _UTILITY_
#define _UTILITY_
#include <iostream>
#include "Matrix.h"
#include "MatrixIO.h"

template <typename T>
void printMatrix(Numeric_lib::Matrix<T, 2> & toPrint) {
    std::cout << toPrint.dim1() << " " << toPrint.dim2() << std::endl;
    std::cout << "{\n";
    for (Numeric_lib::Index i = 0; i < toPrint.dim1(); ++i) {
        std::cout << "{";
        for (Numeric_lib::Index j = 0; j < toPrint.dim2(); ++j) {
            std::cout << " " << toPrint(i,j) << " ";
        }
        std::cout << "}\n";
    }
    std::cout << "}\n";
}

template <typename T>
void createMatrix (std::vector<std::vector<T> > & matrix, Numeric_lib::Matrix<T, 2> & res) {
    try {
        if ((Numeric_lib::Index) matrix.size() != res.dim1() || (Numeric_lib::Index)matrix[0].size() != res.dim2()) {
            throw std::invalid_argument("The dimensions of RHS and LHS matrices must be equal");
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    for (Numeric_lib::Index i = 0; i < res.dim1(); i++) {
        for (Numeric_lib::Index j = 0; j < res.dim2(); j++) {
            //std::cout << matrix[i][j];
            res(i, j) = matrix[i][j];
        }
    }
}
#endif