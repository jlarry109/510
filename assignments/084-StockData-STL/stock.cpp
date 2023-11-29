#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "StockData.hpp"

std::ifstream openFile(std::string name) { 
    std::ifstream in(name);
    if (!in.is_open()) {
        std::cerr << "Unable to open " << name << std::endl;
        exit(EXIT_FAILURE);  // since we are in function, return would go back to main
    }
    return in;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " stockDataFile\n";
        return EXIT_FAILURE;
    }

    std::ifstream inputFile = openFile(argv[1]);

    std::vector<StockData> data;
    std::string line;

    std::getline(inputFile, line);
    while (std::getline(inputFile, line)) {
        data.push_back(StockData::fromString(line));
    }
   
    // Insert assignment code
    // Calculate daily rates of return
    std::vector<double> returns;
    for (size_t i = 1; i < data.size(); ++i) {
        double rateOfReturn = data[i].rateOfReturn(data[i - 1]);
        returns.push_back(rateOfReturn);
    }

    // Calculate average, max, and min using STL functions
    double averageReturn = accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    auto maxReturnIter = max_element(returns.begin(), returns.end());
    auto minReturnIter = min_element(returns.begin(), returns.end());

    // Find corresponding dates for max and min returns
    size_t maxIndex = distance(returns.begin(), maxReturnIter);
    size_t minIndex = distance(returns.begin(), minReturnIter);

    // Print results
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Daily Return: " << averageReturn << "%" << std::endl;
    std::cout << "Largest Gain: " << *maxReturnIter << "% on " << data[maxIndex + 1].date << std::endl;
    std::cout << "Largest Loss: " << *minReturnIter << "% on " << data[minIndex + 1].date << std::endl;
    return EXIT_SUCCESS;
}