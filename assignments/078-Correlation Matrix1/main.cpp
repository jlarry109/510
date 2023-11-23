#include <iostream>
#include <cstdlib>
#include <fstream>
#include "utility.h"
#include "asset.h"

int main (int argc, char ** argv) {
    exitWithFailure(argc != 2, "Incorrect number of argument count. Usage: ./programName inputFile.txt");
    process(argv[1]);
    return EXIT_SUCCESS;
}