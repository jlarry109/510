1. Create a file "answer.txt".
2. Execute the code under the instructions by hand as demonstrated with the memory/trace diagrams in class.
3. Write the output in your "answer.txt" file.
4. Take a picture of your diagram.
5. Create a Makefile to compile test.cpp into a program called "test".
6. Execute `./test` and compare the output to that you expected in answer.txt.  Make the necessary corrections to your diagrams and answer.txt.
7. Submit answer.txt, Makefile, and your diagram (this can be png/jpg/pdf) for grading.

```c++
#include <string>
#include <iostream>
using namespace std;

class Link {
public:
    string value;
    Link* prev;             
    Link* succ;
    Link(const string& v, Link* p = nullptr, Link* s = nullptr) : value{v}, prev{p}, succ{s} { }
};

Link* insert(Link* p, Link* n) {       // insert n before p; return n
    if (n==nullptr) {
        return p;
    }
    if (p==nullptr) {
        return n;
    }
    n->succ = p;                      // p comes after n
    if (p->prev) {
        p->prev->succ = n;
    }
    n->prev = p->prev;                // p’s predecessor becomes n’s predecessor
    p->prev = n;                      // n becomes p’s predecessor
    return n;
}

void print_all(Link* p) {
    cout << "{ ";
    while (p) {
        cout << p->value;
        p = p->succ;
        if (p) {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

int main() {
    Link* norse_gods = new Link{"Thor"};
    norse_gods = insert(norse_gods,new Link{"Odin"});
    norse_gods = insert(norse_gods,new Link{"Freia"});
    print_all(norse_gods);
}
``` 
