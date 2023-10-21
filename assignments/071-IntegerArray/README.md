# Integer Array
For this problem, you will be writing an `IntArray` class. This class holds an array of ints, as well as the nubmer of elements in the array. The `IntArray` class needs to provide the following functionality:
  - A default constructor: Initalizes the size to 0 and the array to `nullptr`
  - A constructor that takes an int: Initializes the size to the int passed in and the array to
      hold that many ints 
  - A copy constructor: Performs a deep copy
  - An assignment operator: Performs a deep copy
  - A destructor: Releases any allocated memory
  - An `[]` operator
    -  Checks if the index is in bounds. If not, throws an `out_of_range` exception
    o Returns a reference to the appropriate element
    * Note: there are two versions of this operator: 
      ```c++
      int & operator[](int index);
      const int & operator[](int index) const;
      ```
      They will have the exact same code. The difference is that if
      the object they are invoked on is `const`, then the second will
      be used, returning a `const` reference, preventing modification
      of the object.
  - A `size()` function: Returns the size of the arrray
  - An `==` operator: Checks two arrays to see if the have the same contents:
      - Same number of elements
      - Each element is the same as the element in the other array at the same index 
  - A `!=` operator: The opposite of the == operator
  - The `<<` operator should be overloaded on `std::ostream` and `const IntArray &` to print the array.
    - Format:
       ``` 
       {element0, element1, element2, ... elementN-2, elementN-1}
       ```

Four files have been distributed with this assignment:
  - `IntArray.hpp`: provides the header (interface) of this class.  This file should not be modified.  
  - `IntArray.cpp`: provides the implementation of this class. Implement your changes in this file.   
  - `test.cpp`: provides a main to test your array.  You should not need to modify this file.
  - `Makefile`: will compile intArrayTest to test your program.

With the interface and implementation separated between the .hpp and the
.cpp files, the functions in the .cpp file must be named with the
classname and :: operator to indicate what class they live in, e.g.:
```c++
  int IntArray::size() const {
  }
```
This specifies that you are defining the `size()` method in the `IntArray`
class. 

Test, debug, and valgrind your code! We have provided the output of
the test program which the Makefile builds.

Submit `IntArray.cpp` to the Gradescope assignment once you have validated your implementation of IntArray.