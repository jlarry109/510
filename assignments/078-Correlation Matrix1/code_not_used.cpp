/*#include "utility.h"
#include <string>
#include <fstream>

double validateRealNumber(std::string str_num, size_t i){
  const char * num_char_star = str_num.c_str();
  const char* start = num_char_star;
  char* endptr{};
  double num = strtod(start, &endptr);
  // Conversion failed
  std::cout << "num is: " << num << std::endl;
  exitWithFailure(endptr == start && i == 1, "Invalid data passed in for price and no valid previous entry exists");
  // Handle range error, e.g., overflow or underflow
  exitWithFailure(endptr != start && errno == ERANGE, "Range error during conversion");
  if (endptr == start && i > 1) {
    return std::numeric_limits<double>::min();
  }
  return num;
}

void validateInput (std::string  fileName) {
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
    //found = line.find(delimiter, found + 1); //Search for second comma 
    //exitWithFailure(found == std::string::npos, "There must be at least two commas on a line of input");
    //numLines++;
}
inputFile.close();
}

void validateTime (std::string fileName) {
  //Make sure time is a valid value and it's in ascending order
  std::ifstream inputFile(fileName);
  exitWithFailure(!inputFile.is_open(), "Failed to open the file specified");
  std::string line;
  std::string header;
  const std::string delimiter = ",";
  std::getline(inputFile, header);
  while (std::getline(inputFile, line)) {
    std::size_t found = line.find(delimiter);
    exitWithFailure(found == std::string::npos, "There was no commas found on a line of input");
    std::string time_str = line.substr(0, found).c_str();
    size_t pos;
    std::stol(time_str, &pos);
    exitWithFailure(pos != time_str.length(), "Conversion of time value from string to long failed");
}
inputFile.close();
}*/