#include <fstream>
#include <iostream>
#include "solver.hpp"


Matrix2D read_from_file(string filename) {
        std::ifstream input(filename);

        int nrows, ncols = 0;
        input >> nrows;
        input >> ncols;
        Matrix2D M(nrows,ncols);
        input >> M;

        //std::cout << nrows << " " << ncols << "\n";
        //std::cout << M;
	return M;
}

Vector1 makeVector(Matrix2D m) {
	Vector1 v(m.size());
	for (int i=0; i < m.size(); i ++) {
		v(i) = m(0,i);
	}
	return v;
}

int main(int argc, char* argv[])
{

    if (argc !=3) {
        cerr << "Usage: ./gaussian A.txt B.txt\n";
		return EXIT_FAILURE;
    }

	Matrix2D A = read_from_file(argv[1]);

	Matrix2D b2D = read_from_file(argv[2]);
	Vector1 b = makeVector(b2D.slice(0));

	Vector1 x = classical_gaussian_elimination(A, b);
	std::cout << 1  << " " << x.dim1() << "\n";
	std::cout << "{ " << x << " }\n";

}
