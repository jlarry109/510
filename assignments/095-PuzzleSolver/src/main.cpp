#include "kubok.hpp"
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return EXIT_FAILURE;
    }
    Kubok puzzle (argv[1]);
    puzzle.getGrid() = puzzle.kubokSolver();
    std::cout << puzzle << std::endl;
    return EXIT_SUCCESS;
}
