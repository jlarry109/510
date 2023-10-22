# Vector One - Chapter 18

In this assignment, you will enhance your vector1.hpp header file to include features described in Chapter 18

Steps:
1. Copy the `vector1.hpp`, `vector1_tests.cpp`, and `CMakeLists.txt` from the previous assignment
   to this assignment folder.
2. Create a constructor that accepts an initializer list as its argument to your `vector1.hpp` file.  See section 18.2. Test your code.
3. Create a copy constructor for your vector. Section 18.3.1. Test your code.
4. Create a copy assignment for your vector. Section 18.3.2. Test your code.
   
   *Note:* Pay careful attention to the source code changes - need to deallocate the existing elem member as we are replacing the contents of the object with those from another object.

5. Implement the subscript operator `[]` to your vector. Section 18.5.  Note the need to implement both versions. Test your code.
6. Run the following commands:
   ```
   cmake -S . -B build
   cmake --build build
   ```
7. Run the program 'build/vector1' and review the output. It should list all tests as successfully passed.
8. Submit vector1.hpp to the Gradescope assignment.

Note: You should alter `vector1_tests.cpp` to test locally, repeating steps 6 & 7 as necessary.

