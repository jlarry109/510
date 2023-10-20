# Valgrind Exercise 
This assignment is designed to give you practice finding memory leaks using [valgrind](https://valgrind.org/).
While the code is in C++, the program does utilize C-style strings.

C-style strings are an array of characters terminated by a null character `\0`, which
signifies the end of the string.
```c++
    char msg[] = "Hello!";   // msg is a character array of 7 characters 
                             // must allocate space for the `\0` terminator
```

In a previous problem, you executed a Ceaser Cipher encryption program by hand.
That program read an input file, and wrote to standard output.  

In this problem, you are going to work on a slightly modified version of that program,
which is is included in encrypt.cpp.   The major difference between this version
of the program and the previous one is that rather than printing to stdout, 
this program appends ".enc" to the input file name, and writes its output to that
file (for example, if your input file is called "input.txt", it will write to "input.txt.enc").

This program has the basic algorithm correct, but makes a variety of errors---all of which
valgrind will detect.  Your job for this problem is to fix the program by making it 
valgrind cleanly. 

## Hints
- Start from the first valgrind error.  Read and understand the error.  It will
tell you on what line of code valgrind detected the problem.  Understand the
error, and why it is occuring. Fix the error, make, and re-run.  Repeat the process until all valgrind errors are gone. 
- The "Built-in Arrays" Docable discusses C-style strings
- Remember that any time you allocate memory (i.e., use `new`) you must deallocate it with `delete`.
- You can also step through the code with VS Code's debugger or [gdb](https://www.sourceware.org/gdb/).

## Building 
Use the included Makefile to build your executable. Note the inclusion of the
"-ggdb3" flag. This produces debugging information that valgrind will use when
reporting errors.

## Executing
To execute your program with valgrind, use the following command
```
valgrind --leak-check=full ./encrypt 13 README
```
Using a key of 13 is a special case of the Caesar cipher in that repeating the 
executable on the encrypted file will decrypt it. [ROT13](https://en.wikipedia.org/wiki/ROT13)

## MacOS Users
Newer versions of MacOS, specifically those for the Apple silicon chips (M1/M2), do not have valigrind available.  You can either use the class Docker image or use `leaks`:
```
leaks  -atExit -quiet -- ./encrypt 13 README
```

## Submitting
Submit the fixed version of `encrypt.cpp` when the memory errors have been fixed.
