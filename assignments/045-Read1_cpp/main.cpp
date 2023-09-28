#include "std_lib_facilities.h"

int main(void) {
    int a = 3;
    int b = 9;
    while (a <= b) {
        if (a % 2 == 1) {
            cout << "a is " << a << "\n";
        }
        else {
            cout << "b is " << b << "\n";
            for (int i = 0; i < b - a ; i++) {
                cout << "a * i + b = " << a * i + b << "\n";
            }
        }
        a++;
        b--;
    }
    return 0;
}
