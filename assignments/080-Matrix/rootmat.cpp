#include "Matrix.h"
//#include "MatrixIO.h"
#include "string"
#include "cstdlib"
#include <stdexcept>
#include <cmath>
#include "utility.h"
#include <vector>

template <typename T>
void rootMatrix(Numeric_lib::Matrix<T, 2> & mat) {
    for (Numeric_lib::Index i = 0; i < mat.dim1(); i++) {
        for (Numeric_lib::Index j = 0; j < mat.dim2(); j++) {
            mat(i, j) = std::sqrt(mat[i][j]);
        }
    }
}

int main (int argc, char * argv []) {

    int rows, cols;

    // Read matrix dimensions from input
    std::cin >> rows >> cols;

    // Create a 2D vector to store the matrix
    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols, 0));

    char openingMatrixBrace, openingRowBrace;

    // Read the opening brace of the matrix
    std::cin >> openingMatrixBrace;

    for (int i = 0; i < rows; i++) {
        // Check if an opening brace for the row is present
        //std::cout << "row " << i + 1 << std::endl;
        std::cin >> openingRowBrace;

        // Read matrix entries for each row
        for (int j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
            //std::cout << matrix[i][j];
        }
        //std::cout << "End of row" << std::endl;

        // Check if a closing brace for the row is present
        char closingRowBrace;
        std::cin >> closingRowBrace;

        // If a closing brace for the row is present, read the closing brace for the matrix
        if (closingRowBrace == '}' && i == rows - 1) {
            char closingMatrixBrace;
            std::cin >> closingMatrixBrace;
            break;  // Exit the loop after reading the first row if braces encompass the entire matrix
        }
        if(!std::cin.good()) {
            break;
        }
    }
    Numeric_lib::Matrix<double, 2> mat (rows, cols);
    createMatrix(matrix, mat);
    //printMatrix<double>(mat);
    rootMatrix(mat);
    // Display the matrix
    //printMatrix<double>(mat);
    std::cout << mat.dim1() << " " << mat.dim2() << std::endl;
    std::cout << mat << std::endl;
    return EXIT_SUCCESS;
}

