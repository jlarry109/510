/*#include <string>
#include <iostream>
#include <fstream>
//#include <Eigen/Dense>
#include "Eigen/Dense"
#include <vector>
#include <sstream>
#include <iomanip>
#include <utility>
using namespace std;
using namespace Eigen;

void solveOptimization (std::vector<std::vector<double> >& cov, const std::vector<double> & aveReturn, bool r) {
    size_t size = cov.size();
    size_t n = size + 2;
	std::cout << "ROR,volatility" << std::endl;
	for (int i = 1; i <= 26; i++) {
		MatrixXd A(n, n);
		MatrixXd B(n, 1);
		for (size_t x = 0; x < size; x++) {
			for (size_t y = 0; y < size; y++) {
				A(x, y) = cov[x][y];
			}
			B(x, 0) = 0;
			A(x, size) = 1;
			A(size, x) = 1;
			A(x, size + 1) = aveReturn[x];
			A(size + 1, x) = aveReturn[x];
		}
		for (size_t x = size; x < n; x++) {
			for (size_t y = size; y < n; y++) {
				A(x, y) = 0;
			}
		}
		B(size, 0) = 1;
		B(size + 1, 0) = 0.01 * i;
		ColPivHouseholderQR<MatrixXd> dec(A);
	    MatrixXd C = dec.solve(B);
	    if (r) {
	    	// store all negative weight positions
	    	std::vector<int> negatives;
	    	for (size_t i = 0; i < size; i++) {
	    		if (C(i, 0) < 0) {
	    			negatives.push_back(i);
	    		}
	    	}
	    	// until no negative values
	    	while(!negatives.empty()) {
	    		int current = A.rows();
	    		int numNega = negatives.size();
	    		// reculculate
	    		MatrixXd tempA(current + numNega, current + numNega);
	    		MatrixXd tempB(current + numNega, 1);
	    		for (int x = 0; x < current + numNega; x++) {
	    			for (int y = 0; y < current + numNega; y++) {
	    				tempA(x, y) = 0;
	    			}
	    			tempB(x, 0) = 0;
	    		}
	    		// copy AB
	    		for (int x = 0; x < current; x++) {
	    			for (int y = 0; y < current; y++) {
	    				tempA(x, y) = A(x, y);
	    			}
	    			tempB(x, 0) = B(x, 0);
	    		}
	    		// set equition
	    		for (int i = 0; i < numNega; i++) {
	    			tempA(negatives[i], current + i) = 1.0;
	    			tempA(current + i, negatives[i]) = 1.0;
	    		}
	    		negatives.clear();
	    		A = tempA;
	    		B = tempB;
	    		ColPivHouseholderQR<MatrixXd> dec(A);
    			C = dec.solve(B);
    			for (size_t i = 0; i < size; i++) {
      				if (C(i, 0) < 0) {
       					negatives.push_back(i);
      				}
    			} 
	    	}
	    }
	    double result = 0.0;
	    for (size_t x = 0; x < size; x++) {
	    	for (size_t y = 0; y < size; y++) {
	    		result += C(x, 0) * C(y, 0) * cov[x][y];
	    	}
	    }
	    std::cout << std::fixed << std::setprecision(1) << (double) i << "%," << std::setprecision(2) << sqrt(result) * 100 << "%" << std::endl;
	}
}

std::vector<std::vector<double> >computeCovariance(std::vector<double> & sd, std::string corrFileName) {
    size_t size = sd.size();
    std::string line;
    std::ifstream corrFileStream(corrFileName); //CHECK FOR OPEN FAILURE
    if (!corrFileStream.is_open()) {exit(EXIT_FAILURE);}
  	std::vector<std::vector<double> > cov(size);
  	for (size_t i = 0; i < size; i++) {
		if (!corrFileStream.good() || !std::getline(corrFileStream, line)) {
            std::cout << "Here: ";
			std::cerr << "Wrong file format." << std::endl;
			exit(EXIT_FAILURE);
		}
		std::stringstream ssline(line);
		std::string token;
		for (size_t j = 0; j < size; j++) {
			if (!getline(ssline, token, ',')) {
                std::cout << "There:" << ssline.str() << std::endl;
				std::cerr << "Wrong line format" << std::endl;
				exit(EXIT_FAILURE);
      		}
      		cov[i].push_back(atof(token.c_str()) * sd[i] * sd[j]);
		}
		if (getline(ssline, token, ',')) {
            std::cout << "Here and There: ";
			std::cerr << "Wrong line format" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	if (corrFileStream.good() && std::getline(corrFileStream, line)) {
		std::cerr << "Wrong file format" << std::endl;
		exit(EXIT_FAILURE);
	}
    corrFileStream.close();
    return cov;
}


// Function to compute covariance matrix
vector<vector<double>> computeCovariance(const vector<double>& sd, const vector<vector<double>>& correlations) {
    size_t size = sd.size();
    vector<vector<double>> cov(size, vector<double>(size, 0.0));

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            cov[i][j] = correlations[i][j] * sd[i] * sd[j];
        }
    }

    return cov;
}
pair<vector<double>, vector<vector<double>>> readFiles(const string& universeFileName, const string& correlationFileName) {
    ifstream universeStream(universeFileName);
    ifstream correlationStream(correlationFileName);

    if (universeStream.fail() || correlationStream.fail()) {
        cerr << "Failed to open one of the files." << endl;
        exit(EXIT_FAILURE);
    }

    vector<double> averageReturns;
    vector<vector<double>> covariance;

    string line;
    while (universeStream.good() && getline(universeStream, line)) {
        stringstream ssline(line);
        vector<string> tokens;
        for (string token; getline(ssline, token, ','); tokens.push_back(token));

        try {
            averageReturns.push_back(atof(tokens[1].c_str()));
        } catch (...) {
            cerr << "Failed to read universe." << endl;
            exit(EXIT_FAILURE);
        }
    }

    while (correlationStream.good() && getline(correlationStream, line)) {
        stringstream ssline(line);
        vector<double> row;

        string token;
        while (getline(ssline, token, ',')) {
            row.push_back(atof(token.c_str()));
        }

        covariance.push_back(row);
    }

    return make_pair(averageReturns, covariance);
}



std::pair<std::vector<double>, std::vector<double> > readFile (std::string  univ_fileName, std::string  corr_fileName) {
    std::vector<double> aveReturn;
  	std::vector<double> sd;
    std::ifstream univFileStream(univ_fileName); //CHECK FOR OPEN FAILURE
	std::ifstream corrFileStream(corr_fileName); //CHECK FOR OPEN FAILURE
  	std::string line;
  	while (std::getline(univFileStream, line)) {
  		std::stringstream ssline(line);
  		std::vector<std::string> tokens;
  		for (std::string token; std::getline(ssline, token, ','); tokens.push_back(token));
  		// to catch errors
  		try {
  			aveReturn.push_back(atof(tokens[1].c_str()));
  			sd.push_back(atof(tokens[2].c_str()));
  		} catch(...) {
	    	std::cerr << "failed to read universe" << std::endl;
	    	exit(EXIT_FAILURE);
  		}
  	}
  	
  	std::pair<std::vector<double>, std::vector<double> > res;
    res.first = aveReturn;
    res.second = sd;
  	univFileStream.close();
  	corrFileStream.close();
    for (auto d : aveReturn) {
        std::cout << "d is: " << d << std::endl;
        }
    return res;
    
}

int main(int argc, char ** argv) {
	if (argc != 4 && argc != 3) {
		std::cerr << "Usage: ./efficient_frontier (-r) universe.csv correlation.csv" << std::endl;
    	exit(EXIT_FAILURE);
	}
	bool r = false;
	if (argc == 4) {
		std::string flag(argv[1]);
        if (flag == "-r") {
            r = true;
        }
		else {
			std::cerr << "./efficient_frontier (-r) universe.csv correlation.csv" << std::endl;
    		exit(EXIT_FAILURE);
		}
	}

	// read files
	ifstream u_stream(argv[argc - 2], ifstream::in); //univ_fileName
	ifstream c_stream(argv[argc - 1], ifstream::in); //corr_fileName
	if (u_stream.fail() || c_stream.fail()) {
	    cerr << "failed to open one of the files." << endl;
	    exit(EXIT_FAILURE);
  	}
    std::pair<std::vector<double>, std::vector<double> > readResult = readFile(argv[argc - 2], argv[argc - 1]);
  	std::vector<double> aveReturn = readResult.first;
  	std::vector<double> sd = readResult.second;

  	
  	std::vector<std::vector<double> > cov = computeCovariance(sd, argv[argc - 2]);
    solve(cov, aveReturn, sd.size(), r);
    
    if (argc != 4 && argc != 3) {
        cerr << "./efficient_frontier (-r) universe.csv correlation.csv" << endl;
        exit(EXIT_FAILURE);
    }

    bool allowShortSales = (argc == 4 && string(argv[1]) == "-r");

    auto filesData = readFiles(argv[argc - 2], argv[argc - 1]);
    const vector<double>& averageReturns = filesData.first;
    const vector<vector<double>>& correlations = filesData.second;

    vector<double> standardDeviations; // You may need to compute sd from covariances

    // Update this line based on how you compute standard deviations
    vector<vector<double>> covariances = computeCovariance(standardDeviations, correlations);

    solveOptimization(covariances, averageReturns, allowShortSales);
  	int size = sd.size();
  	vector<vector<double> > cov(size);
  	for (int i = 0; i < size; i++) {
		if (!c_stream.good() || !getline(c_stream, line)) {
			cerr << "Wrong file format." << endl;
			exit(EXIT_FAILURE);
		}
		stringstream ssline(line);
		string token;
		for (int j = 0; j < size; j++) {
			if (!getline(ssline, token, ',')) {
				cerr << "Wrong line format" << endl;
				exit(EXIT_FAILURE);
      		}
      		cov[i].push_back(atof(token.c_str()) * sd[i] * sd[j]);
		}
		if (getline(ssline, token, ',')) {
			cerr << "Wrong line format" << endl;
			exit(EXIT_FAILURE);
		}
	}
	if (c_stream.good() && getline(c_stream, line)) {
		cerr << "Wrong file format" << endl;
		exit(EXIT_FAILURE);
	}
    */

	// calcualte and print
	/*int n = size + 2;
	cout << "ROR,volatility" << endl;
	for (int i = 1; i <= 26; i++) {
		MatrixXd A(n, n);
		MatrixXd B(n, 1);
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				A(x, y) = cov[x][y];
			}
			B(x, 0) = 0;
			A(x, size) = 1;
			A(size, x) = 1;
			A(x, size + 1) = aveReturn[x];
			A(size + 1, x) = aveReturn[x];
		}
		for (int x = size; x < n; x++) {
			for (int y = size; y < n; y++) {
				A(x, y) = 0;
			}
		}
		B(size, 0) = 1;
		B(size + 1, 0) = 0.01 * i;
		ColPivHouseholderQR<MatrixXd> dec(A);
	    MatrixXd C = dec.solve(B);
	    if (r) {
	    	// store all negative weight positions
	    	vector<int> negatives;
	    	for (int i = 0; i < size; i++) {
	    		if (C(i, 0) < 0) {
	    			negatives.push_back(i);
	    		}
	    	}
	    	// until no negative values
	    	while(!negatives.empty()) {
	    		int current = A.rows();
	    		int numNega = negatives.size();
	    		// reculculate
	    		MatrixXd tempA(current + numNega, current + numNega);
	    		MatrixXd tempB(current + numNega, 1);
	    		for (int x = 0; x < current + numNega; x++) {
	    			for (int y = 0; y < current + numNega; y++) {
	    				tempA(x, y) = 0;
	    			}
	    			tempB(x, 0) = 0;
	    		}
	    		// copy AB
	    		for (int x = 0; x < current; x++) {
	    			for (int y = 0; y < current; y++) {
	    				tempA(x, y) = A(x, y);
	    			}
	    			tempB(x, 0) = B(x, 0);
	    		}
	    		// set equition
	    		for (int i = 0; i < numNega; i++) {
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
	    double result = 0.0;
	    for (int x = 0; x < size; x++) {
	    	for (int y = 0; y < size; y++) {
	    		result += C(x, 0) * C(y, 0) * cov[x][y];
	    	}
	    }
	    cout << fixed << setprecision(1) << (double) i << "%," << setprecision(2) << sqrt(result) * 100 << "%" << endl;
	}
  	u_stream.close();
  	c_stream.close();
  	return EXIT_SUCCESS;
}


*/