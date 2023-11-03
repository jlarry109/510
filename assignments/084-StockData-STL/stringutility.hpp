#include <string>
#include <vector>

/**
 * @brief Split apart a line based upon delimiters in the string
 * 
 * @param line The string to be split
 * @param delim a string specifying the delimeter used to split apart the string
 * @return a vector of string objects
 */
std::vector<std::string> splitLine(std::string line, std::string delim);