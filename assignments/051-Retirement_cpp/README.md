# Retirement in C++

This programming assignment implements the same functionality as the first 
retirement exercise in Python.  This "retirement savings" calculator models 
the effect of saving a fixed amount each month while earning a particular 
rate of return as an individual works.  Then, in retirement, we subtract a 
fixed amount each month for living expenses while earning a smaller rate of 
return. For this model, we'll remove the effects of inflation by keeping 
everything in "today's dollars" and using a "Rate of return" that is in 
terms of "more than inflation".

As with Python and many other programming languages, C++ is object-oriented.  Rather than relying upon the built-in types such as int and double, we can create our own types with the keyword class to abstract various "things". To abstract the concept of time, contribution, and rate of return, we will create a simple class in C++ that contains these three elements.
```
    class RetireInfo {
        public:
        int months;
        double contribution;
        double rate_of_return;
    };
```
Unlike Python, C++ enforces access control to the members and methods within 
objects.  Using the public keyword, code outside of the class definition can 
directly access those member elements. To define a new variable and 
initialize the values, you can use the following:
```
    RetireInfo working;
    working.months = 120;
    working.contribution = 5000;
    working.rate_of_return = 0.095/12;
```
You can now use retire_info anywhere you can use a built-in data type 
such as bool.

As you've seen in the assignments so far, C++ uses the concept of "streams" 
to model input and output. The term stream implies characters are written 
or read sequentially. C++ provides the "insertion"/"output" operator << to 
send data to an output stream.  To modify the flow of those characters, we 
can place special method calls into the stream.  To output data in the 
correct format for this assignment, use the following line:

cout << "Age " << setw(3) << years << " month " << setw(2) << months << " you have $" << fixed << setprecision(2) << balance << "\n";
 

Steps:
  1. Create a file called "retirement.cpp". Include the usual header file (std_lib_facilities.h) at the top.
  2. Model savings (while working) and expenditures (while retired) using the retire_info class.
  3. Write the function
     ```
     /**
      * @brief Calculates and prints the current balance as an individual works and retires
      *
      * @param startAge The time in months when the model beings
      * @param initial The initial amount of savings an individual has
      * @param working Details for the model about how long an individual  works with savings and investment gains
      * @param retired Details for the model about how long the individual lives in retirement with expenditures and continued investment gains
      */
     void retirement (int startAge, double initial, RetireInfo working, RetireInfo retired) 
     ```
     While the individual works, the function:
       - Computes the retirement account balance each month while working. To do this, 
         calculate the account balance increase from returns (balance * rate of return) 
         and add that to the current balance. Then, add the monthly contribution to the 
         balance. For example, if you have $1,000 in the account, earn a 0.5% rate of 
         return per month, and contribute $100 per month,
         balance = balance + balance * 0.005 + 100
      - Print the current balance using the above line.

     These tasks repeat for the number of months specified in the working object. 
   
     Next, repeat these same steps but with the retired information.
   
     Code Improvement: Since the function performs similar steps for both  working and retired, look to abstract that part into its own function. That way, you re-use code rather than duplicate code.
 

4. Write a main function that computes the retirement with these assumptions:
   ```
    Working:
        Months: 489
        Per Month Savings: $1000
        Rate of Return: 4.5% per year ( 0.045/12 per month)

    Retired:
        Months: 384
        Per Month Spending: $4000
        Rate of Return: 1% per year ( 0.01/12 per month)
    
    Starting conditions:
        Age: 327 months (27 years, 3 months)
        Savings: $21345
    ```
5. You can compile your code by executing `make` on the command line (i.e., in a terminal window). This program looks for a Makefile that contains commands to compile your program.

   To execute the program: `./retirement`

   To execute the program and redirect the output in a file: `./retirement > file.txt`
   To compare your output to the provided output: `diff retirment_ans.txt file.txt`
 
6. Once your output matches,  submit retirement.cpp to Gradescope.