#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "utility.h"
#include "asset.h"
#include <stdexcept>

double validateRealNumber(std::string str_num, size_t i, size_t j) {
  /*
  Validates and converts a string representing a real number to a double.
  
  @param str_num The input string to be converted.
  @param i The row number in the CSV file.
  @param j The column number in the CSV file.
  
  @return If j is 0 (date/time entry), returns i - 1. Otherwise, returns the converted double value.
  
  @throws std::invalid_argument if the conversion fails due to invalid input.
  @throws std::out_of_range if the conversion results in a range error (e.g., overflow or underflow).
  
  @note If an exception is caught, the program may exit with failure based on specific conditions.
 */
    if (j == 0) { //If it's the date/time entry, return the row number - 1. Had to improvise after learning that the time column can be any format (eg. date)
        return i - 1;
    }
    try {
      double num = std::stod(str_num);
      return num;
} catch (const std::invalid_argument& e) {
    // Conversion failed
      exitWithFailure(i == 1, "Invalid data passed in for price and no valid previous entry exists");
      return std::numeric_limits<double>::min();
} catch (const std::out_of_range& e) {
    // Handle range error, e.g., overflow or underflow
      exitWithFailure(true, "Range error during conversion");
      return std::numeric_limits<double>::min();
}
}

void validateInput (std::string  fileName) {
  /**Validates the input file, checking for proper formatting.
  * 
  * @param fileName The name of the input file to be validated.
  * 
  * @throws std::runtime_error if the file fails to open.
  * @throws std::runtime_error if a line in the file does not contain at least one comma.
  **/
  std::ifstream inputFile(fileName);
  exitWithFailure(!inputFile.is_open(), "Failed to open the file specified");
  std::string line;
  std::string header;
  //size_t numLines = 0;
  const std::string delimiter = ",";
  std::getline(inputFile, header);
  while (std::getline(inputFile, line)) {
    // Make sure there are at least one comma on  each line of input
    std::size_t found = line.find(delimiter);
    exitWithFailure(found == std::string::npos, "There must be at least one comma on a line of input");
    //numLines++;
}
inputFile.close();
}

/*Prints the names of assets in a given vector.
  * 
  * @param assets A vector containing Asset objects.
  */
void printAssets (std::vector<Asset> & assets) {
  for (Asset asset : assets) {
    std::cout << asset.getName() << std::endl;
  }
}

/*Creates a correlation matrix based on the given vector of assets.
  * 
  * @param assets A vector containing Asset objects.
  * @return A dynamically allocated Matrix<double> representing the correlation matrix.
  */
Matrix<double>* createCorrelationMatrix(std::vector<Asset>& assets) {
    size_t size = assets.size();
    Matrix<double> * covMatrix = new Matrix<double>(size, size);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
          if(i == j) {
            //Diagonal elements are set to 1.00
            (*covMatrix)[i][j] = 1.00;
          }
          else {
            //Divide by their standard deviations to get the correlation matrix (in lieu of covariance matrix)
            (*covMatrix)[i][j] = assets[i].calculateCovariance(assets[j]) / (assets[i].getStandardDeviation() * assets[j].getStandardDeviation());
          }
        }
    }
    return covMatrix;
}

 /* Converts a vector of strings to a vector of doubles, validating and handling missing or invalid data. 
  * @param line A vector of strings representing a row of data.
  * @param i The row index.
  * @param previous A vector of vectors containing previous valid data for handling missing values.
  * @return A vector of doubles representing the converted data.
  */
std::vector<double> stringToDouble(std::vector<std::string> & line, size_t i, std::vector<std::vector<double> > & previous) {
  std::vector<double> result;
  for (size_t j = 0;  j < line.size(); j++) {
    std::string num_str = line[j];
    double num_double = validateRealNumber(num_str, i, j);
    if (num_double == std::numeric_limits<double>::min()) {
      assert(j < previous[previous.size() - 1].size());
      num_double = previous[previous.size() - 1][j];
    }
    result.push_back(num_double);
  }
  return result;
}

/*
 * Splits a string into a vector of substrings using the specified delimiter.
 * Validates and exits if any substring is empty.
 * @param s The string to be split.
 * @param delimiter The delimiter used to split the string.
 * @return A vector of substrings.
 */
std::vector<std::string> splitString (std::string & s, std::string delimiter) {
  size_t startn_pos = 0, endn_pos, delimiter_len = delimiter.length();
  std::string str;
  std::vector<std::string> result;
  while ((endn_pos = s.find(delimiter, startn_pos)) != std::string::npos) {
    str = s.substr(startn_pos, endn_pos - startn_pos);
    startn_pos = endn_pos + delimiter_len;
    result.push_back(str);
  }
  result.push_back(s.substr(startn_pos));
  for (std::string str : result) {
    exitWithFailure(str.empty(), "Cannot have an empty field in file!");
  }
  return result;
}

/*
 * Reads the content of a file and returns each line as a vector of strings.
 * 
 * @param fileName The name of the file to be read.
 * @return A vector of strings, where each string represents a line from the file.
 */
std::vector<std::string> readFile(std::string fileName) {
  std::vector<std::string>  inputLines;
  std::ifstream inputFile(fileName);
  // Validate input or exit if the file cannot be opened
  exitWithFailure(!inputFile.is_open(), "Failed to open the file specified");
  std::string line;

  // Read each line from the file and store it in the vector
  while (std::getline(inputFile, line)) {
    inputLines.push_back(line);
  }
  return inputLines;
}

/*
 * A templated utility function:
 * Prints the content of a vector of vectors to the standard output. 
 * @tparam T The type of elements in the vector.
 * @param toPrint The vector of vectors to be printed.
 */
template <typename T>
void printVectOfVect(std::vector<std::vector<T> > & toPrint) {
  for (std::vector<T> vec : toPrint) {
      for (T val : vec) {
        std::cout << val << " ";
      }
      std::cout << std::endl;
    }
}

/*
 * Process the input file, perform initial validation, and calculate correlations.
 *
 * @param inputFileName The name of the input file.
 */
void process(const std::string & inputFileName) {
    //perform initial validation, validata comma separation, etc
    validateInput(inputFileName);
    //read data from file
    std::vector <std::string> inputLines = readFile(inputFileName);
    if (inputLines.size() == 0) {
      std::cout << "Empty file was provided as input" << std::endl;
      return;
    } 
    //split each line and return a vector of strings of size numAssets + 1 (including the time/date)
    std::vector<std::vector<std::string> > splittedLines;
    for (std::string s : inputLines) {
      splittedLines.push_back(splitString(s , ","));
    }
    //Extract the title/heading
    std::vector<std::string> header = splittedLines[0];
    size_t headerSize = header.size();
    std::vector<std::vector<double> > doubles_splittedLines;
    for (size_t i = 1; i < splittedLines.size(); i++) {
      exitWithFailure(headerSize != splittedLines[i].size(), "Lines have different number of columns");
      doubles_splittedLines.push_back(stringToDouble(splittedLines[i], i, doubles_splittedLines));
    }
    //create vector of assets
    std::vector<Asset> assets;
    //start from header[1] -> don't include time column
    for (size_t i = 1; i < header.size(); i++) {
      //create a new asset specifying the asset name
      Asset asset(header[i]);
      //add asset to list of assets
      assets.push_back(asset);
    }
    std::vector<double> previous;
    //Assign previous values to the values of the first line of the file
    previous.assign(doubles_splittedLines[0].begin() + 1, doubles_splittedLines[0].end()); 
    for (size_t i = 1; i < doubles_splittedLines.size(); i++) {
      for (size_t j = 1; j < doubles_splittedLines[i].size(); j++) {
        double previousEntry = previous[j - 1];
        double currEntry = doubles_splittedLines[i][j];
        assets[j - 1].updateAsset(currEntry, previousEntry);////calculate:compute:Rt, average return, and compute standard deviation for each asset
        previous[j - 1] = currEntry;
      }
    }
    // Create my a correlation 
    Matrix<double> * covMatrix = createCorrelationMatrix(assets);
    // Print all the assetNames by calling a printAsset() function passing in a const reference to the AssetNames vector
    printAssets(assets);
    //Print the matrix using the overloaded ostream in the Matrix class
    std::cout << *covMatrix << std::endl;
    // free or (delete) matrices used
    delete covMatrix;
}