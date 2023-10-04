1. Create a file "answer.txt".
2. Execute the code under the instructions by hand as demonstrated with the memory/trace diagrams in class.
3. Write the output in your "answer.txt" file.
4. Take a picture of your diagram.
5. Compile and execute ref.cpp. Compare the output to that expected.  Make any necessary corrections. 
6. Submit your answer.txt file and your diagram (this can be png/jpg/pdf) for grading.

```c++
#include <iostream>
#include <cstdlib>

class AClass {
private:
    int x;
    int y;

public:
    AClass(): x(0), y(0) {
        std::cout << "Making AClass\n";
    }
    AClass(int _x, int _y): x(_x), y(_y) {
        std::cout << "Making AClass(" << x << "," << y << ")\n";
    }

    ~AClass() {
        std::cout << "Destroying AClass(" << x << "," << y << ")\n";
    }

    int & max()  {
        if (x > y) {
            return x;
        }
        return y;
    }

    void set(int _x, int _y) {
        x = _x;
        y = _y;
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

AClass * someFunction(int a, int b) {
    AClass * x = new AClass(a+2, b*8);
    AClass y(a*4-3,b+2);
    x->max() = y.max() - 3;
    return x;
}

int main(void) {
    AClass a(3,4);
    int & r = a.max();
    AClass * b = someFunction(r,2);
    a.set(b->getY(), b->getX() - 3);
    delete b;
    r = 9;
    return EXIT_SUCCESS;
}
```
