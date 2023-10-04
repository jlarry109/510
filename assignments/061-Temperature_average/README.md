# Temperature Average

In this assignment, you'll read in a series of temperatures from an input
file specified as a command-line argument to your program, temperature.
```
./temperature fileName.txt
```
Each line in the file contains a single integer. You may assume the data is valid.

You will need to compute the average of these values and output the 
average, minimum, maximum values in the following format:
```
Minimum Temperature:    XX
Maximum Temperature:    XX
Max Temp as octal:     ooo
Max Temp as hex:        hh
Average Temperature: XX.XX
```

Validations:
- Two command line arguments.  If not, print a usage statement and return with EXIT_FAILURE
- The file does open successfully and return EXIT_FAILURE as the status code if it does not.
- For both of those failures, output an appropriate error message to standard error (`cerr`).

The sample file outputs the following:
```
Minimum Temperature:    56
Maximum Temperature:   100
Max Temp as octal:     144
Max Temp as hex:        64
Average Temperature: 85.29
```

Your code should be in a single file, `temperature.cpp`.

Once your output matches, submit `temperature.cpp` for grading.