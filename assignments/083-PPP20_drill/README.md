# Chapter Drill 20: Iterators

This assignment's goal is to provide practice with iterators and generic functions.

Iterators in the C++ Standard Template Library (STL) follow a common interface:
- access an element by using a dereferencing operator: `*`
- move to the next element by using the `++` operator

The STL also defines the concept of an iterator range - a pair of iterators, each
of which refers to an element or to one past the last element in the same
container. Typically, these iterators are referred to as `begin` and `end`.
The name `end`, though, is a bit misleading in that the second iterator does 
not actually refer to the last element of the range but rather to a point one
past the last element.  It is possible to reach `end` by repeatedly incrementing `begin`.
As such `end` can never precede `begin`.

The elements in the range include the element denoted by `begin` and every element
from `begin` up to but not including `end`.  This element range is called a 
*left-inclusive interval* and is mathematically notated as [`begin`, `end`).

Left-inclusive ranges have three properties that affect programming:
- If `begin` equals `end`, the range is empty.
- If `begin` is not equal to `end`, at least one element exists in the range;
  `begin` refers to the first element in that range.
- `begin` can be incremented some number of times until `begin == end`.

With these properties, we can now safely write loops to process a range of elements:
```c++
while (begin != end) {
	*begin = val;      // access begin - dereference to assign or access the value
	begin++;           // move to the next element
}
```

Not by chance, these same properties apply to pointers and access contiguous memory
addresses in an array. Consider the following code - 
```c++
char str[] = "Hello";     // allocates a character array with 6 elements - str[5] = '\0'
char *p = &str[0];        // p holds the memory address of the first element
while (p != &str[5]) {    // loop until we reach the end.  *p != '\0' is equivalent
    cout << *p << "\n";   // derefencing p to get the current character
    p++;                  // move p to the next element
}
```
`p` functions the same as `begin` while `str[5]` functions as `end`.

For this assignment, you'll need to create a source file named `ch20_drill.cpp` and complete each of the following steps: 

1. Define a built-in array, a vector, and a list, each containing the ten elements: 
   `{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }`.
2. In the array, vector, and list:
   - increase the value of each element in the array by 2
   - increase the value of each element in the vector by 3 
   - increase the value of each element in the list by 5
3. Using the following template, write a simple `copy()` operation named `copy2()`:
   ```c++
   template<typename Iter1, typename Iter2>
   Iter2 copy2(Iter1 f1, Iter1 e1, Iter2 f2);
   
   ```
   that copies [f1,e1) to [f2,f2+(e1–f1)) and returns f2+(e1–f1) just like the 
   standard library copy function. Note that if f1==e1, the sequence is empty, 
   so there is nothing to copy, but this should fall out in the `while` loop.
4. Use your `copy2()` to copy the array into the vector and to copy the list into the array. 
5. Print out the contents of the final array, list, and vector. This should be in the following
   format:
   ```
   array: {14, 13, 12, 11, 10, 9, 8, 7, 6, 5}
   vector: {11, 10, 9, 8, 7, 6, 5, 4, 3, 2}
   list: {14, 13, 12, 11, 10, 9, 8, 7, 6, 5}
   ```
6. Submit your completed ch20_drill.cpp file to Gradescope.

## Notes:
- Ideally, your program's `main()` should only have 11 statements:
  - 3 to initialize the define and initialize the containers
  - 3 to call a function that increases the containers as defined above
  - 2 to call `copy2()` as specified
  - 3 to call a function to print your containers
- You should write the `print()` function as part of step 1 to validate your work.
- As with `copy2()`, `print()` and the function to increase elements should be generic functions.


## References
1. Lippman, Stanley B., Josée Lajoie, and Barbara E. Moo. _C++ Primer_. 5th Edition. 2013.
2. Stroustrup, Bjarne. _Programming: Principles and Practice Using C++_. 2nd Edition. 2014.