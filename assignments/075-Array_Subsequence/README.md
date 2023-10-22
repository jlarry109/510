# Array Subsequence - CPP

This assignment repeats a Python assignment, but using C++.

1.  Create a file, `maxSeq.hpp`, that declares the function:
    ```
    /*!
       Finds the maximum length of an increasing contiguous subsequence
       in a built-in array. The subsequence just needs to be increasing, 
       not necessarily increasing by any particular pattern or rate.

       If array is undefined(i.e., equals nullptr), returns 0
      
       \param array pointer to the start of an int array
       \param n size of the array
       \return the length of the maximum increasing contiguous subsequence
     */
    size_t maxSeq(int *array, size_t n);
    ```

2. Create another file, `maxSeq.cpp`, with an implementation of maxSeq.
3. You should then create a `main.cpp` along with a Makefile to test and validate
   your implementation.
4. Submit `maxSeq.hpp` and `maxSeq.cpp` to the Gradescope assignment.


As an example, `int a[] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9}` has a max subsequence length of 4.