#include <iostream>

// Code From
// Programming: Principles and Practice Using C++ (2nd Edition)
// Bjarne Stroustrup

using namespace std;

int main() {
    try {
        int x = 4; 
        double d = 5/(x - 2); 
        if (d = 2 * x + 0.5) {
            cout << "Success!\n";
        }
        return 0;
    }
    catch (exception& e) {
        cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        cerr << "Oops: unknown exception!\n";
        return 2;
    }
}
