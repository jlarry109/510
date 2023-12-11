#ifndef __T_KUBOK_H___
#define __T_KUBOK_H___
//#include <ortools/linear_solver/linear_solver.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <numeric>
#include <cassert>
#include <algorithm>
#include <iomanip> // Add this line for setw
const int SIZE = 4;

class Kubok {
private:
    std::vector<int> rowSum;
    std::vector<int> colSum;
    std::vector<std::vector<int> > grid; 
 

    bool solve(size_t row, size_t col);
    bool isValidPlacement(size_t row, size_t col, int num);
    bool contains(int value);
    int getRowSum(const std::vector<int>& row);
    int getColSum(size_t col);
    std::vector<int> getColumnSums();
    std::vector<int> getColumn(size_t col);
    
    
public:
    Kubok();
    explicit Kubok(const std::string fileName);
    ~Kubok();
    std::vector<int> & getRowSum();
    std::vector<int> & getColSum();
    std::vector<std::vector<int> > & getGrid();
    std::vector<std::vector<int>> kubokSolver();
    void splitCommaSeparatedLines(std::vector<int> & ans, const std::string & line);
    void parseColRowSumLines(std::vector<int> & ans, const std::string & colRowSumline, std::string sumType);
    bool isValidInput();
    void processFile(const std::string & fileName);
    friend std::ostream& operator<<(std::ostream& os, const Kubok& rhs);
};

std::ostream& operator<<(std::ostream& os, const Kubok& obj);

#endif
