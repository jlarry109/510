#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void encrypt(ifstream &f, int key, ofstream &outfile) {
    string *line = new string;
    while (getline(f,*line)) {
        char* ptr = (*line).data();
        while (*ptr != '\0') {
            char c = *ptr;
            if (isalpha(c)) {
                c = tolower(c);
                c -= 'a';
                c += key;
                c %= 26;
                c += 'a';
            }
            *ptr = c;
            ptr++;
        }
        outfile << *line << "\n";
    }
    delete line;
}


int main(int argc, char **argv) {
    int key;
    ifstream inputFile;

    if (argc != 3) {
        cerr << "Usage: encrypt key inputFileName\n";
        return EXIT_FAILURE;
    }

    try {
        key = std::stoi(argv[1]);
    }
    catch (invalid_argument& e) {
        cerr << "Invalid key (" << argv[1] << "): must be a non-zero integer\n";
        return EXIT_FAILURE;
    }

    inputFile.open(argv[2], std::ifstream::in);
    if (!inputFile.is_open()) {
        cerr << "Unable to open input file: " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    char *outFileName =  new char [(strlen(argv[2]) + 5)];

    strcpy(outFileName, argv[2]);
    strcat(outFileName, ".enc");

    ofstream outFile{outFileName};
    if (!outFile) {
        cerr << "can't open output file: " << outFileName << "\n";
        return EXIT_FAILURE;
    }
    encrypt(inputFile,key, outFile);
    delete [] outFileName;
    return EXIT_SUCCESS;
}
