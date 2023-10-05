# Vector, Catch2 and CMake

In this assignment, you will create a header file containing Chapter 17's final version of vector and run unit tests for it using a testing framework, Catch2 and a new build tool, CMake.

Steps:
1. Create a file `vector1.hpp` containing the `class vector` code from section 17.6. 
   Name the class `vector1` (to avoid name clashes with the standard library's vector class.)

2. Read the file `vector1_tests.cpp` to see some simple tests for the vector1 class. In an 
   upcoming assignments, you will be writing your own tests.
   
3. Read the file 'CMakeLists.txt', which is a kind of makefile for the 'cmake' 
   build tool. Note that it creates an executable 'vector1' using the test source code.

4. Run the following commands:
   ```
   cmake -S . -B build
   cmake --build build
   ```

5. Run the program 'build/vector1' and review the output. It should list all tests as successfully passed.

6. Submit vector1.hpp to Gradescope.
