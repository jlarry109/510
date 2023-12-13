#include "kubok.hpp"
using namespace std;
int safeStringToInt(const std::string& s) {
    try {
        size_t pos;  // To store the position of the first invalid character
        int result = std::stoi(s, &pos);

        // Check if there are any invalid characters after the valid integer
        if (pos < s.length()) {
            std::cerr << "Error: Invalid characters after the integer." << std::endl;
            exit(EXIT_FAILURE);  // Or handle the error in an appropriate way
        }

        return result;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid argument. Not a valid integer." << std::endl;
        exit(EXIT_FAILURE);  // Or handle the error in an appropriate way
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Out of range. The integer is too large or too small." << std::endl;
        exit(EXIT_FAILURE);  // Or handle the error in an appropriate way
    }
}
/*
    Validates the input for the Kubok puzzle by checking the following criteria:
    1. Ensures that the sizes of colSum, rowSum, and grid are all equal to SIZE.
    2. Verifies that each row of the grid has a size equal to SIZE.
    3. Checks if the sums in colSum and rowSum are within the valid range [10, 58].
       Displays an error message and returns false if any sum is outside this range.
    4. Ensures that the numbers in the grid are within the valid range [0, 16] and not repeated.
       Displays an error message and returns false if any number is out of range or repeated.
    
    Returns:
    - true: If the input passes all validation checks.
    - false: If any of the validation checks fail, with corresponding error messages printed.
*/
bool Kubok::isValidInput() {
    // Validate sizes
    if (colSum.size() != SIZE || rowSum.size() != SIZE || grid.size() != SIZE) {
        std::cout << "Incorrect dimensions of Inputs: Grid size is: " << grid.size() << " rowSum size is: " << rowSum.size() << " and colSum size is: " << colSum.size() << std::endl;
        return false;
    }

    for (size_t i = 0; i < SIZE; ++i) {
        if (grid[i].size() != SIZE) {
            std::cout << "Incorrect row size. Row:" << i + 1 << std::endl;
            return false;
        }
    }

    // Validate sums range
    for (size_t i = 0; i < SIZE; ++i) {
        if (!(10 <= colSum[i] && colSum[i] <= 58) || !(10 <= rowSum[i] && rowSum[i] <= 58)) {
            std::cout << "Invalid range for colSum or rowSum entry" << std::endl;
            return false;
        }
    }

    // Validate puzzle numbers
    std::vector<bool> seen(17, false);
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            int num = grid[i][j];
            // if an entry is outside the valid range of [0, 16] or is with [1, 16] and repeated (duplicates), return false
            if (!(0 <= num && num <= 16) || (num != 0 && seen[num])) { 
                std::cout << "entry is: " << num << std::endl;
                std::cout << "Invalid range for grid entries issue" << std::endl;
                return false;
            }
            seen[num] = true;
        }
    }

    return true;
}

/*
    Parses a comma-separated line into integers and stores them in the provided vector.

    Parameters:
    - ans: Vector for storing parsed integers.
    - line: Input string with comma-separated values.

    Exits with EXIT_FAILURE if the number of entries on the current row is not equal to SIZE.
*/
void Kubok::splitCommaSeparatedLines(std::vector<int> & ans, const std::string & line) {
    std::stringstream ssline(line);
    size_t i = 0;
    for (std::string token; getline(ssline, token, ','); ans[i++] = safeStringToInt(token));
    if (i != SIZE) {
        std::cerr << "Invalid number of entries on current row. Column " << i + 1 << " is missing" << std::endl;
        exit(EXIT_FAILURE);
    }
}

/*
    Solves the Kubok puzzle using a recursive method.
    Calls the private recursive solving method (solve) starting from the top-left corner (0, 0).
    Returns:
    - If a solution is found, returns the solved grid.
    - If no solution is found, prints an error message to std::cout, returns an empty vector.
*/
std::vector<std::vector<int>> Kubok::kubokSolver() {
        // Call the recursive solving method
    if (solve(0, 0)) {
            return grid; // Return the solved grid
        } else {
            std::cout << "No solution found!" << std::endl;
            return std::vector<std::vector<int>>(); // Return an empty vector for no solution
        }
    }

/*
    Recursive solving method for the Kubok puzzle.
    
    Parameters:
    - row: Current row index.
    - col: Current column index.

    Returns:
    - true if a valid solution is found.
    - false otherwise.

    Implementation Details:
    - Base case: If all rows are filled, checks column sums against colSum.
    - Checks row sum before moving to the next row.
    - Skips already filled cells and backtracks if an invalid placement is encountered.
    - Tries valid placements for numbers from 1 to 16.

    Note: Modifies the 'grid' member variable during the solving process.
*/
   bool Kubok::solve(size_t row, size_t col) {
        if (row == grid.size()) {
            // All rows are filled, check column sums
            return getColumnSums() == colSum;
        }

        if (col == grid[row].size()) {
            // Check row sum before moving to the next row
            if (getRowSum(grid[row]) != rowSum[row]) {
                return false;
            }
            return solve(row + 1, 0);
        }

        // Skip already filled cells
        if (grid[row][col] != 0) {
            return solve(row, col + 1);
        }

        for (int num = 1; num <= 16; num++) {
            if (isValidPlacement(row, col, num)) {
                grid[row][col] = num;
                if (solve(row, col + 1)) {
                    return true;
                }
                grid[row][col] = 0; // Backtrack
            }
        }

        return false;
    }

    /*
    Checks if placing a number at a given position in the Kubok grid is valid.

    Parameters:
    - row: Row index for the placement.
    - col: Column index for the placement.
    - num: Number to be placed.

    Returns:
    - true if the placement is valid.
    - false otherwise.
    */
    bool Kubok::isValidPlacement(size_t row, size_t col, int num) {
        return !contains(num) && !contains(num)
                && getRowSum(grid[row]) + num <= rowSum[row]
                && getColSum(col) + num <= colSum[col];
    }

    /*
    Checks if a given value is present in the Kubok grid.
    Returns true if the value is found, false otherwise.
    */

    bool Kubok::contains(int value) {
        //return std::find(array.begin(), array.end(), value) != array.end();
        for (auto & array : grid) {
            if(std::find(array.begin(), array.end(), value) != array.end()) {
                return true;
            }
        }
        return false;
    }

    /*
        Overloaded getRowSum: Calculates the sum of values in a given row of the Kubok grid.
        Returns the computed sum.
    */
    int Kubok::getRowSum(const std::vector<int>& row) {
        return std::accumulate(row.begin(), row.end(), 0);
    }

    /*
    Retrieves the values in a specified column of the Kubok grid.
    Returns a vector containing the column values.
*/

    std::vector<int> Kubok::getColumn(size_t col) {
        std::vector<int> column;
        for (const auto& row : grid) {
            column.push_back(row[col]);
        }
        return column;
    }

    /*
    Calculates the sum of values in a specified column of the Kubok grid.
    Returns the computed sum.
    */
    int Kubok::getColSum(size_t col) {
        std::vector<int> column = getColumn(col);
        return std::accumulate(column.begin(), column.end(), 0);
    }

    /*
        Returns a reference to the vector containing row sums in the Kubok puzzle.
    */

    std::vector<int> & Kubok::getRowSum() {
        return rowSum;
    }

    /*
        Returns a reference to the vector containing column sums in the Kubok puzzle.
    */

    std::vector<int> & Kubok::getColSum() {
        return colSum;
    } 

    /*
        Returns a reference to the two-dimensional vector representing the Kubok puzzle grid.
    */
    std::vector<std::vector<int> > & Kubok::getGrid() {
        return grid;
    }

    /*
        Calculates and returns a vector containing the column sums of the Kubok puzzle grid.
    */

    std::vector<int> Kubok::getColumnSums() {
        std::vector<int> colSums(grid[0].size(), 0);
        for (size_t i = 0; i < grid[0].size(); i++) {
            colSums[i] = getColSum(i);
        }
        return colSums;
    }

/*
    Parses a line containing column or row sums and populates the provided vector.

    Parameters:
    - ans: Reference to the vector for storing parsed sums.
    - colRowSumline: Input string containing column or row sums.
    - sumType: Indicates whether the line represents column or row sums.

    Implementation Details:
    - Finds the position of the colon (':') to separate the sum type and the actual sums.
    - Checks for the presence of a colon and verifies the correct sum type.
    - Calls the splitCommaSeparatedLines method to parse and store the individual sums.

    Error Handling:
    - Exits the program with EXIT_FAILURE if the line format is incorrect.
*/
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

/*
    Processes a Kubok puzzle input file to initialize the puzzle.

    Parameters:
    - fileName: Path to the input file.

    File Format:
    - Expects lines starting with "col sums:", "row sums:", and "grid:".
    - Parses and populates colSum and rowSum vectors based on the corresponding lines.
    - Reads and parses the grid entries line by line.

    Error Handling:
    - Exits the program with EXIT_FAILURE if there are issues with file opening,
      incorrect file format, or invalid input.

    Note: Calls the parseColRowSumLines and splitCommaSeparatedLines methods.
*/
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
    if(line != "grid:") {
        std::cerr << "Found " << "'" << line << "'" << " instead of 'grid:'" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    size_t i = 0;
    while(std::getline(inputFile, line)) {
        if (i >= SIZE) {
            std::cerr << "Incorrect number of rows in grid" << std::endl;
            exit(EXIT_FAILURE);
    }
        splitCommaSeparatedLines(grid[i], line);
        i++;
    }
    if (i != SIZE) {
            std::cerr << "Incorrect number of rows in grid" << std::endl;
            exit(EXIT_FAILURE);
    }
    inputFile.close();
    // Validate input
    if (!isValidInput()) {
        std::cerr << "Error: Invalid input file format." << std::endl;
        exit(EXIT_FAILURE);
    }

}

/*
    Overloaded output stream operator for printing the Kubok puzzle.

    Parameters:
    - os: Reference to the output stream.
    - rhs: Reference to the Kubok puzzle object to be printed.

    Output Format:
    - The first line contains column sums.
    - Subsequent lines display each row along with the corresponding row sum.
    - Numbers are formatted with setw(2) for proper alignment.

    Returns:
    - Reference to the modified output stream.
*/
std::ostream& operator<<(std::ostream& os, const Kubok& rhs) {
    // Print column sums in the first line
    os << "   "; 
    for (size_t i = 0; i < SIZE; ++i) {
        os  << " "  << std::setw(2) << rhs.colSum[i];
    }
    os << std::endl;

    // Print each row along with the corresponding row sum
    for (size_t i = 0; i < SIZE; ++i) {
        os << std::setw(3) << rhs.rowSum[i]/* << " "*/;
        for (size_t j = 0; j < SIZE; ++j) {
            os << std::setw(3)<< rhs.grid[i][j]/* << " "*/;
        }
        if (i < SIZE - 1) {
            os << std::endl;
        }
    }
    return os;
}

/*
    Default constructor for the Kubok puzzle.

    Initializes:
    - rowSum: Vector with SIZE elements, all initialized to 0.
    - colSum: Vector with SIZE elements, all initialized to 0.
    - grid: Two-dimensional vector with SIZE rows and SIZE columns, all initialized to 0.
*/

Kubok::Kubok() : rowSum(SIZE, 0), colSum (SIZE, 0), grid(SIZE, std::vector<int>(SIZE, 0)) {}


/*
    Parameterized constructor for the Kubok puzzle, initializes from an input file.

    Parameters:
    - fileName: Path to the input file.

    Initializes:
    - rowSum: Vector with SIZE elements, all initialized to 0.
    - colSum: Vector with SIZE elements, all initialized to 0.
    - grid: Two-dimensional vector with SIZE rows and SIZE columns, all initialized to 0.

    Calls the processFile method to populate the puzzle based on the content of the input file.
*/

Kubok::Kubok(const std::string fileName) : rowSum(SIZE, 0), colSum(SIZE, 0), grid(SIZE, std::vector<int>(SIZE, 0)) {
    processFile(fileName);
}


/*
    Destructor for the Kubok puzzle.
    (No explicit cleanup or resource release needed.)
*/

Kubok::~Kubok() {}