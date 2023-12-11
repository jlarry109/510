/*#include "kubok.hpp"

bool Kubok::isValidInput() {
    // Validate sizes
    if (colSum.size() != SIZE || rowSum.size() != SIZE || grid.size() != SIZE) {
        std::cout << "size issue" << std::endl;
        return false;
    }

    for (int i = 0; i < SIZE; ++i) {
        if (grid[i].size() != SIZE) {
            std::cout << "size[i] issue" << std::endl;
            return false;
        }
    }

    // Validate sums range
    for (int i = 0; i < SIZE; ++i) {
        if (!(10 <= colSum[i] && colSum[i] <= 58) || !(10 <= rowSum[i] && rowSum[i] <= 58)) {
            std::cout << "Valid sums range issue" << std::endl;
            return false;
        }
    }

    // Validate puzzle numbers
    std::vector<bool> seen(17, false);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int num = grid[i][j];
            if (!(0 <= num && num <= 16) || (num != 0 && seen[num])) {
                std::cout << "num is: " << num << std::endl;
                std::cout << "Invalid range for grid entries issue" << std::endl;
                return false;
            }
            seen[num] = true;
        }
    }

    return true;
}

void Kubok::parseColRowSumLines(std::vector<int> & ans, const std::string & colRowSumline, std::string sumType){
    size_t colPos = colRowSumline.find(':');
    if (colPos == std::string::npos) {
        std::cout << "no colon in line" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(colRowSumline.substr(0, colPos) != sumType) {
        std::cout << colRowSumline.substr(colPos) << std::endl;
        std::cout << "There must be a " << sumType << " on a " << sumType << " line" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line = colRowSumline.substr(colPos + 1);
    splitCommaSeparatedLines(ans, line);
}

std::ostream& operator<<(std::ostream& os, const Kubok& rhs) {
    // Print column sums in the first line
    os << "  "; 
    for (int i = 0; i < SIZE; ++i) {
        os << " " << std::setw(2) << rhs.colSum[i];
    }
    os << std::endl;

    // Print each row along with the corresponding row sum
    for (int i = 0; i < SIZE; ++i) {
        os << rhs.rowSum[i] << " ";
        for (int j = 0; j < SIZE; ++j) {
            os << std::setw(2)<< rhs.grid[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}
Kubok::Kubok() : rowSum(), colSum (), grid(4, std::vector<int>(4, 0)) {}

void Kubok::processFile(const std::string & fileName) {
    std::string line;
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::getline(inputFile, line); // Read "col sums:" line
    parseColRowSumLines(colSum, line, "column sums");

    getline(inputFile, line); //Read "row sums:" line
    parseColRowSumLines(rowSum, line, "row sums");

    std::getline(inputFile, line); //Read "grid:"
    assert(line == "grid:");
    size_t i = 0;
    while(std::getline(inputFile, line)) {
        std::cout << "splitting lines for actual grid" << std::endl;
        splitCommaSeparatedLines(grid[i], line);
        i++;
    }
    
    inputFile.close();
    //printPuzzle(puzzle, colSums, rowSums);
    // Validate input
    if (!isValidInput()) {
        std::cerr << "Error: Invalid input file format." << std::endl;
        exit(EXIT_FAILURE);
    }

}
Kubok::Kubok(const std::string fileName) : rowSum(), colSum(), grid(4, std::vector<int>(4, 0)) {
    processFile(fileName);
}

Kubok::~Kubok() {}
*/