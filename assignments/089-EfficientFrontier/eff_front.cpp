/*#include <iostream>
#include <fstream>
#include "Eigen/Dense"
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace Eigen;
double convertToDouble(const std::string &str) {
    try {
        size_t pos;
        double result = stod(str, &pos);
        if (pos < str.size()) {
            throw std::invalid_argument("Invalid double: " + str);
        }
        return result;
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("Invalid double: " + str);
    }
}
// Function to exit the program with a failure message if a specified condition is true.
void exitWithFailure(const bool failureCondition, const std::string &failureMessage) {
    if (failureCondition) {
        std::cerr << failureMessage << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Function to read universe and correlation files and return the data.
std::pair<std::vector<double>, std::vector<std::vector<double>>> readFiles(const std::string &universeFileName, const std::string &correlationFileName) {
    std::ifstream universeStream(universeFileName);
    std::ifstream correlationStream(correlationFileName);

    // Exit if the files failed to open.
    exitWithFailure(!universeStream.is_open() || !correlationStream.is_open(), "Failed to open input files.");

    std::vector<double> averageReturn;
    std::vector<double> sd;
    std::string line;

    // Read universe file.
    while (universeStream.good() && std::getline(universeStream, line)) {
        std::stringstream ssline(line);
        std::vector<std::string> tokens;

        // Tokenize the line.
        for (std::string token; getline(ssline, token, ','); tokens.push_back(token));

        // Try to convert tokens to double and add to vectors.
        try {
            averageReturn.push_back(convertToDouble(tokens[1]));
            sd.push_back(convertToDouble(tokens[2]));
        } catch (...) {
            exitWithFailure(true, "Failed to read universe.");
        }
    }

    // Initialize covariance matrix with zeros.
    std::vector<std::vector<double>> cov(sd.size(), std::vector<double>(sd.size(), 0.0));

    // Read correlation file and compute covariance.
    for (int i = 0; i < (int)sd.size(); ++i) {
        exitWithFailure(!correlationStream.good() || !getline(correlationStream, line), "Incorrect file format specified.");
        std::stringstream ssline(line);
        std::string token;

        for (int j = 0; j < (int)sd.size(); ++j) {
            if (!getline(ssline, token, ',')) {
                std::cerr << "Incorrect file format specified." << endl;
                exit(EXIT_FAILURE);
            }
            try {
                cov[i][j] = convertToDouble(token) * sd[i] * sd[j];
            }catch (...) {
                exitWithFailure(true, "Failed to read universe.");
            }
        }
        if (getline(ssline, token, ',')) {
            std::cerr << "Incorrect file format specified." << endl;
            exit(EXIT_FAILURE);
        }
    }
    exitWithFailure(correlationStream.good() && getline(correlationStream, line), "Incorrect file format specified.");

    return make_pair(averageReturn, cov);
}

// Function to calculate and print the efficient frontier.
void solveAndPrint(const vector<double> &averageReturn, const vector<vector<double>> &cov, const bool r) {
    int size = averageReturn.size();
    int n = size + 2;
    std::cout << "ROR,volatility" << endl;

    // Loop through different return values.
    for (int i = 1; i <= 26; i++) {
        MatrixXd A(n, n);
        MatrixXd B(n, 1);
        // Build the matrix A and vector B.
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                A(x, y) = cov[x][y];
            }
            B(x, 0) = 0;
            A(x, size) = 1;
            A(size, x) = 1;
            A(x, size + 1) = averageReturn[x];
            A(size + 1, x) = averageReturn[x];
        }
        // Set the lower right block of A to zeros.
        for (int x = size; x < n; x++) {
            for (int y = size; y < n; y++) {
                A(x, y) = 0;
            }
        }

        // Set the last two elements of B.
        B(size, 0) = 1;
        B(size + 1, 0) = 0.01 * i;

        // Solve the linear system.
        ColPivHouseholderQR<MatrixXd> dec(A);
        MatrixXd C = dec.solve(B);

        // If short selling is not allowed, iterate until all weights are non-negative.
        if (r) {
            vector<int> negatives;

            for (int i = 0; i < size; i++) {
                if (C(i, 0) < 0) {
                    negatives.push_back(i);
                }
            }

            while (!negatives.empty()) {
                int current = A.rows();
                int numNegs = negatives.size();

                MatrixXd tempA(current + numNegs, current + numNegs);
                MatrixXd tempB(current + numNegs, 1);

                for (int x = 0; x < current + numNegs; x++) {
                    for (int y = 0; y < current + numNegs; y++) {
                        tempA(x, y) = 0;
                    }
                    tempB(x, 0) = 0;
                }

                for (int x = 0; x < current; x++) {
                    for (int y = 0; y < current; y++) {
                        tempA(x, y) = A(x, y);
                    }
                    tempB(x, 0) = B(x, 0);
                }

                for (int i = 0; i < numNegs; i++) {
                    tempA(negatives[i], current + i) = 1.0;
                    tempA(current + i, negatives[i]) = 1.0;
                }

                negatives.clear();
                A = tempA;
                B = tempB;
                ColPivHouseholderQR<MatrixXd> dec(A);
                C = dec.solve(B);

                for (int i = 0; i < size; i++) {
                    if (C(i, 0) < 0) {
                        negatives.push_back(i);
                    }
                }
            }
        }
        // Calculate portfolio volatility.
        double result = 0.0;
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                result += C(x, 0) * C(y, 0) * cov[x][y];
            }
        }
        // Print results.
        cout << fixed << setprecision(1) << (double)i << "%," << setprecision(2) << sqrt(result) * 100 << "%" << endl;
    }
}

int main(int argc, char **argv) {
    // Check command line arguments.
    exitWithFailure(argc != 4 && argc != 3, "Usage: ./efficient_frontier (-r) universe.csv correlation.csv"); 
    bool r = false;
    // Check if the -r flag is present.
    r = (argc != 4) ? false : (strcmp(argv[1], "-r") == 0) ? true : false;
    exitWithFailure(argc == 4 && !r, "Usage: ./efficient_frontier (-r) universe.csv correlation.csv");
    // Read data from files.
    auto data = readFiles(argv[argc - 2], argv[argc - 1]);
    // Calculate and print the efficient frontier.
    solveAndPrint(data.first, data.second, r);
    return EXIT_SUCCESS;
}
*/
