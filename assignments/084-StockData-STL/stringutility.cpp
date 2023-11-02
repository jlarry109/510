#include "stringutility.hpp"

std::vector<std::string> splitLine(std::string line, std::string delim) {
    std::vector<std::string> result;

    auto start = 0U;
    auto end = line.find(delim);
    while (end != std::string::npos) {
        result.push_back(line.substr(start, end - start));
        start = end + delim.length();
        end = line.find(delim, start);
    }
    std::string last = line.substr(start, end);
    if (last.length()) {
        result.push_back(last);
    }

    return result;
}