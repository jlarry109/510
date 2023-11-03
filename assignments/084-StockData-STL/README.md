# Stock Data and the STL

For the assignment, you'll practice using the C++ Standard Template Library (STL)
to generate standard descriptive statistics fora given stock over a period of
time.

Many stock research services provide daily stock data in CSV format where the data
files look like - 
```
Date,Open,High,Low,Close,Volume
10/02/2023,171.22,174.3,170.93,173.75,52164539
10/03/2023,172.26,173.63,170.82,172.4,49594609
10/04/2023,171.09,174.21,170.97,173.66,53020289
```

In the distribution folder, seven files have been provided:
1. __StockData.hpp__ declares a StockData class to track individual records
   from a file. Note that this class as a static method (i.e., the method
   belongs to the class) to create a StockData object from a string.
2. __StockData.cpp__ implements the StockData class.
3. __stringutility.hpp__ declares a function that splits apart a string by a delimiter.
4. __stringutility.cpp__ implements the the `splitline()` function.
5. __stock.cpp__ provides the main function. You'll implement the assignment 
  functionality in this file.
6. __Makefile__ generates the stock executable.
7. __appl_202310.csv__ contains Apple's stock data from October 2023.

Within the main function, you need to create a vector containing the rates of
returns for the closing prices from one day to the next. You may assume that the dates are 
correctly in order in the file.  The `StockData` class already contains a method to
compute the percentage rate of return: $ ( \frac{currentClose}{previousclose} - 1) * 100.0 $

From that vector, you need to compute the average rate of return, find the maximum 
rate of return, and find the minimum rate of return. You should not directly use any 
iteration to  compute these values but rather use these functions from STL:
- [accumulate()](https://en.cppreference.com/w/cpp/algorithm/accumulate)
- [max_element()](https://en.cppreference.com/w/cpp/algorithm/max_element)
- [min_element()](https://en.cppreference.com/w/cpp/algorithm/min_element)

Note: You need to use STL iterators such as [begin()](https://en.cppreference.com/w/cpp/iterator/begin) 
and [end()](https://en.cppreference.com/w/cpp/iterator/end) with those functions.

Then, print out the results to standard output (`std::cout`) as follows:
Average Daily Return: -0.08%
Largest Gain: 1.48% on 20231006
Largest Loss: -2.46% on 20231026

The date is already formatted correctly, however you need to access the correct date in the `data` vector
by using [std::distance](https://en.cppreference.com/w/cpp/iterator/distance) function.

Once you have validated your results, submit `stock.cpp` to the Gradescope assignment.
