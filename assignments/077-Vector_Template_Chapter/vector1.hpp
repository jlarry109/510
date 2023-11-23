// a very simplified templated vector class
#include <assert.h>
#include <initializer_list>
#include <iterator>
#include "std_lib_facilities.h"

template <typename T>
class vector1 {
    private:
        int sz; // the size
        T * elem; // a pointer to the elements
        int space;
    public:
        vector1() : sz(0), elem(NULL), space(0) {}
        vector1(int s) :sz(s), elem(new T [s]), space(s) { } //constructor
        vector1(std::initializer_list<T> values) : sz (values.size()), elem( new T [sz]) {
            // Contructing using an initializer list
            int i = 0;
            for (T value : values) {
                elem[i] = value;
                i++;
            }
        }
        vector1 (const vector1 & rhs): sz(rhs.sz), elem(new T [rhs.sz] ) {//copy constructor
            for (int i = 0; i < sz; i++) {
                elem[i] = rhs.elem[i];
            }
        }
        vector1 & operator = (const vector1 & rhs) { //copy assignment operator
            if (this != &rhs) { //check for self assignment : don't want to end up with a dangling pointer!
                T * temp = new T [rhs.sz];
                for (int i = 0; i < rhs.sz; i++) {
                    temp[i] = rhs.elem[i];
                }
                delete [] elem;
                elem = temp;
            }
            return *this;
        }

        T & operator[](const int index) { // [] operator
            if(!(index >= 0 && index < sz)) {
                throw Range_error(index);
            }
            return elem[index];
        }
        const T & operator[](const int index) const { // overloaded [] operator
            if(!(index >= 0 && index < sz)) {
                throw Range_error(index);
            }
            return elem[index];
        }
        ~vector1() { delete[] elem; } //destructor
        int size() const { return sz; } // the current size
        T get(int n) { return elem[n]; }  //access: read
        void set(int n, T v) { elem[n]=v; }  //access: write
        int capacity() const { return space; }
        void reserve (int reserve_size) {
            if (reserve_size <= space) {
                return;
            }
            T * p = new T [reserve_size];
            for (int i = 0; i < sz; i++) {
                p[i] = elem[i];
            }
            delete [] elem;
            elem = p;
            space = reserve_size;
        }

        void resize(int new_size) {
            reserve(new_size);
            for (int i= sz; i < new_size; i++) {
                elem[i] = 0;
            }
            sz = new_size;
        }

        void push_back (T d) {
            if (space == 0) {
                reserve(8); //Let's start with space for 8 elements
            }
            else if (sz == space) { reserve(2 * space);} //get more space
            elem[sz] = d; //add at end
            sz++;
        }

};