# Evaluative Assignment: Correlation Matrix
This is an *evaluative* assignment. That means that we want you to
show us what you know/what you can do (as opposed to most assignments,
which are to practice and learn from). 

Accordingly, you may not work with anyone else on this assignment. All
work must be your own. By submitting your work to Gradescope you are
agreeing to the academic integrity section at the bottom of this document.

For this assignment, you will write the first step toward your final evaluative assignment. Ultimately, you will write a program that, given a universe of assets, creates the optimal portfolios by calculating the efficient frontier, as described in your portfolio theory module. 

For this part, given historical price data, you will calculate the correlation matrix for a universe (set) of assets. At a high level, your program should:
1. Read historical price data from a file. 
2. For each asset, calculate the rate of return for each time step.
3. For each asset, calculate the average return and standard deviation.
4. Calculate the covariance matrix for all the assets. 
5. Calculate the correlation matrix for all the assets.

## Inputs
The system will read an input file specified as a command-line argument.
This file is a CSV (comma-separated values) file with a header row.  The first column in the header row is the label for the “time index” field. The remaining columns are asset names. (A variable number of assets may be present. At least one asset name will be present.)

The remaining rows specify the “time index”, followed by the price of each asset at that time. You may assume that there are no missing rows. Note in year.csv that some of the prices are null. Your program should handle null or non-numeric data in some fields by repeating the previous valid price for that asset. (Of course, if there is no valid data in a column, that is an error – print a message to stderr and exit with EXIT_FAILURE.)

```
Time,A,B
0,2193.03,24848.53
1,2291.72,25723.20
2,2349.01,26955.34
3,2373.67,27963.47
4,2297.72,28385.72
```
Sample Input File: `small.csv`

## Processing
For each change in the “time index” (i.e., row - it does not matter if the data is daily, monthly, or something else), you should compute the rate of return.  The rate of return can be calculated as

$
R_t = \begin{Bmatrix}
\text{ not valid for initial record }
\\ 
\frac{asset_t}{asset_{t-1}} -1 \text{ if t > 1}
\end{Bmatrix} 
$

Rates of returns for `A` in the sample input file: `0.04500166, 0.02499869, 0.01049804, -0.0319969`

Once you have the rates of return, compute the average return and standard deviation for that asset. The standard deviation is calculated as follows: 
(N = # of changes in the time index, which is 1 less than the number of data records (excluding first row))

$ R_{\bar{x}} = \frac{\sum_{t=1}^{N}R_t}{N} $ = average(mean) rate of return for asset $x$

$\sigma_x = \sqrt{\frac{\sum_{t=1}^{N}(R_t- R_{\bar{x}})^2}{N-1}}$ = standard deviation of those rates of return for asset $x$



For asset A:
- $ R_{\bar{x}} =0.01212538 $
- $ \sigma_x = 0.03263941 $

Next, you’ll need to create the covariance matrix, where each element is the covariance of two assets at that row and column.  So the covariance for assets a and b:

$ cov_{a,b} = \frac{1}{N}\sum_{t=1}^{N} (R_{A,t} - R_{A,\bar{x}})(R_{B,t}-R_{B,\bar{x}}) $

Covariance Matrix = 
$
\begin{bmatrix}
cov_{1,1} & cov_{1,2} & \cdots & cov_{1,n} \\ 
cov_{2,1} & cov_{2,2} & \cdots & cov_{2,n} \\ 
\cdots    & \cdots    & \cdots & \cdots    \\ 
cov_{n,1} & cov_{n,2} & \cdots & cov_{n,n} 
\end{bmatrix}
$

Finally, you will need to compute the correlation matrix. 
$\rho_{a,b} = \frac{cov_{a,b}}{\sigma_a\sigma_b} $

Correlation Matrix = 
$
\begin{bmatrix}
\ 1         & \rho_{1,2} & \cdots & \rho_{1,n} \\ 
\rho_{1,2} & 1          & \cdots & \rho_{2,n} \\ 
\cdots     & \cdots     & \cdots & \cdots    \\ 
\rho_{1,n} & \rho_{2,n} & \cdots & 1 
\end{bmatrix}
$

Recall that $-1 < \rho_(a,b) < 1$, where positive correlation means assets change in the same direction, and negative correlation means assets change in opposite directions. Therefore, the correlation of an asset with itself should be exactly 1. Note, however, that these formulas will not give you exactly $\rho_(a,a) =1 $ but will approach 1 for large time series of data. For this project, let $\rho_(a,a)$  be exactly 1 instead of doing the correlation computation.

## Output
Your program should print the result to stdout as follows:
- list of assets, separated by newlines
- [correlation matrix]

Note: The matrix must be formatted with open and closed square brackets and comma-delimited values, such that each floating-point number has 7 spaces and four digits after the decimal point. See ios_base::width, setprecision, and fixed in the C++ library.

The files `small.out` and `year.out` contain sample output.

## Implementation Requirements
1. Create a Makefile that compiles your code to an executable named “correl_matrix”.
2. Your executable takes exactly 1 command-line argument – the name of the file to read. The specification is described in the input section. Two sample files have been provided: `small.csv` and `year.csv`

For full credit, your program must valgrind cleanly - i.e., not have any memory leaks or invalid memory reads. Of course, you should test your program on many more inputs than those provided. You will also be graded on code quality. This means your code should make good use of abstraction, have good variable, function, and class names, be well commented and formatted, and have at least one class definition. 

## Submission 
Once you have validate and tested your program, submit your Makefile and all associated code files (.cpp/.hpp) to the Gradescope assignment.  All work must be submitted prior to the submission deadline in Gradescope. A 30% penalty will be applied to any late submission.

## Grading
As this is an evaluative assignment, you will receive a small portion of your grade prior to grading deadline and the rest afterwards.
| Portion            | Precentage|
|--------------------| ---------:|
|Prior to Submission | 80%|
|Post Submission     | 15%|
|Code Review         |  5%|

## Implementation Approach
While you are free to implement this in any way that is reasonable, here are some recommendations:
- Create an Asset class
  - State: name, time series rate of return, average return, and standard deviation. 
  - Behavior: calculate the average return, standard deviation, covariance, correlation
- A mechanism to represent a matrix.  Some possibilities:
  - Another class (e.g,  repurpose the IntMatrix assignment)
  - typedef a vector of vectors of doubles
  - double **matrix
  - Utilize the Matrix class as described in PPP Chapter 24 and used in the Matrix and Gaussian assignments.  This combined work may also be helpful in the next evaluative assignment.
- Separate your source code into multiple files. One idea is to have files: main.cpp, parse.cpp, asset.hpp, and asset.cpp.  


## Academic Integrity
Note: This is an evaluative assignment!  By submitting this assignment, you agree that you have adhered to the following rules:
- Your work must be your own!
- You may NOT consult with other students about:
    - high-level approaches,
    - how to implement your algorithm in code, or
    - how to debug your code.

  (Basically, you may not discuss anything particular to this assignment).
- You may NOT look at another student's code, nor show your code to anyone else.
- You are responsible for keeping your code private.
- You may not look for solutions to this or similar problems online.
- You may not use code from any other source.
- You may not use any AI assistive technology (e.g., ChatGPT)
- You MAY consult _Programming: Principles and Practice Using C++_ and use
  any source code provided through that resource
- You MAY consult any docable page provided for this class.
- You MAY consult  cppreference.com.
- You MAY consult any C++ book on the O'Reilly Learning Platform
- You MAY consult notes you wrote in your notebook.
- You MAY consult the man pages.
- You MAY ask the professor or TAs for clarification on the assignment.
 
If you use code from one of the approved sources.  You should reference that source in a comment just prior to the function or code section. This includes any prior formulative assignments.
