# Linked List-Based Integers

C++ limits the possible values of numeric types by the underlying bit-based representation.
For example, an unsigned short variable stores values between 0 and 65535; C++ implementations
typically represent `short` variables using 2 bytes of memory.   $2^{16} = 65535$

One way to represent integers of arbitrary length is to use a linked-listed data structure where each node of the list represents a single digit of the integer.

In this approach, the linked-list representation of 1842 would be -

```
[2] -> [4] -> [8] -> [1] -> nullptr
```
Note that the first element of the list stores the least significant digit.

In the distribution folder, we have provided four files:
1. __IntegerLinkedList.hpp__ declares two classes: 
   - `IntegerLinkedListNode` represents a digit in the number and contains a self-referential pointer
     to the next digit.
   - `IntegerLinkedList` represents the overall number and contains methods such as addition and equality.
      Note that this class follows the "rule of five" by implementing the various constructors
      and assignment operators.
2. __IntegerLinkedList.cpp__ implements part of the `IntegerLinkedList`. You will
   need to implement the undefined methods in this file.
3. __main.cpp__ provides the main function. Add code to this file to validate your program.
4. __Makefile__ generates the `test` executable.

## Specific Functions to Implement

- `+`: Implement the plus operator to add two `IntegerLinkedList` numbers.
- `==`: Implement the equality comparison operator
- `!=`: Implement the not equals comparison operator
- `<<`: Override the insertion stream operator to print the number onto the stream
- `deallocateNodes()`: Implement this method to free all memory associated with the linked list.
- `fromInt()`: provide a static method that creates an IntegerLinkList from an `int`.
- `fromString()`: provide a static method that creates an IntegerLinkedList from a string. 

## Notes
- You only need to handle positive numbers.
- You do not need to handle an empty string.
- You only need to worry about numbers in base-10 representation.

## Assignment Review Questions
In a file called `answers.txt`, answer the following questions.

1. What is the big-O runtime of `appendDigit()`?
2. Suppose we added a variable in `IntegerLinkList` to track the tail of the linked list.
   What would be the big-O runtime of `appendDigit()` in that situation?
3. Rather than implementing this backed by a linked list, suppose we used `vector`.
   In this case, the least significant digit is in the first index(i.e., `0`).
   What is the big-O runtime of `appendDigit()`?
4. What is the big-O runtime of the addition operation?
5. What is the big-O runtime of the insertion stream operation (`<<`)?

## Submission
Submit `IntegerLinkedList.cpp` and `answers.txt` to the Gradescope assignment.
