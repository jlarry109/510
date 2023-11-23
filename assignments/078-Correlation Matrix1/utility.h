#pragma once
#ifndef _UTILITY_H
#define _UTILITY_H
#include <iostream>
#include <cstdlib>
#include <string>


/*
 * Exit the program with failure if a specified condition is true.
 *
 * @param condition       The condition to check.
 * @param failureMessage  The message to print if the condition is true.
 */
inline void exitWithFailure (bool condition, std::string failureMessage) {
    if (condition) {
        std::cerr << failureMessage << std::endl;
        exit(EXIT_FAILURE);
    }
}
double validateRealNumber(std::string str_num, size_t i, size_t j);
void validateInput(std::string fileName);
void process(const std::string& inputFileName);
#endif