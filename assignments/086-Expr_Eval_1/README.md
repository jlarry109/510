# Expressions - Part One
In this program,  you practice inheritance,
virtual methods, and method overriding to complete a 
simple "calculator" program, which accepts input in "prefix notation".
That is, rather than entering "4 + 3", enter "(+ 4 3)".

This problem is composed of three parts:
- *Part One*: Expressions are limited to numbers and pluses.  Expressions printed but not yet evaluated.
- *Part Two*: Add *, -, and / expressions, but still do not evaluate
- *Part Three*: Add expression evaluation

For the distribution provided:
- `expr.cpp`: reads the input, parses it, and makes "Expression" objects appropriately.
   You should not modify any existing code in this file.  You may choose to implement some functionality
   of the classes you write in this file, although it is probably easier to implement that 
   functionality with the header file you will need to create.  Slightly different versions exist 
   for each part.
- `Makefile`: builds an executable called `expr`.   
- `sample_input.txt`: sample input
- `sample_output.txt`: Corresponding output.  

You need to write an implementation of the "Expression" class and its sub-classes, which will represent the math expression that is read, provide a way to print it "normally" - using infix notation in the format such as (4 + 5), and evaluate an expression to an integer.

Your code must have the following classes with the following functionality
(that is, the parsing code relies on these classes existing, with these names,
the various Expression types being subtype compatible with Expression, and
the classes having the methods and constructors noted below):

*** For Part One ****
```
class Expression
    std::string toString() const = 0;  //abstract method
   
class NumExpression              // must be a subclass of Expression
    NumExpression(long)          // a constructor
    std::string toString() const // implement this method

class PlusExpression             // must be a subclass of Expression
    PlusExpression(Expression * lhs, Expression * rhs)  // a constructor
    std::string toString() const                        // implement this method
```

*** For Part Two ****
```
class MinusExpression              // must be a subclass of Expression
    MinusExpression(Expression * lhs, Expression * rhs)  // a constructor 
    std::string toString() const                         // implement this method

class TimesExpression              // must be a subclass of Expression
    TimesExpression(Expression * lhs, Expression * rhs) // a constructor
    std::string toString() const                        // implement this method

class DivExpression                // must be a subclass of Expression
    DivExpression(Expression * lhs, Expression * rhs)   // a constructor
    std::string toString() const                        // implement this method
```

*** For Part Three ****

Add to Expression:
```
   long evaluate() const = 0; //abstract method
```    
and implement it in the subclasses of Expression.


You may wish to add other classes or methods as you wish.
The various expression types must be a subclass of Expression but do not
have to extend it directly. If you see similarities between some of these
classes that you wish to pull out into another class "in-between" Expression
and those classes, you are welcome (and encouraged) to do so.  

You will want to implement portions of this functionality by overriding methods
and relying on dynamic dispatch.

A few concrete details:

 1. Expression representation:  An expression (+ E1 E2) will result in
    a new PlusExpression with E1 as its lhs (first argument to the constructor)
    and E2 as its rhs (second argument to the constructor). MinusExpression, 
    TimesExpression, and DivExpression function the same way.

    A number (like 9 or -27) will result in a new NumExpression being created,
    with the numeric value of that number passed as the argument to the constructor.

 2. The parser will never make a copy or assign objects by value.  You do not
    need to worry about operator= or the copy constructor.  Each expression
    object will be created with "new" and will be referenced by at most
    one other Expression object (as either the lhs or rhs of a +,-,*, or /).

 3. When an expression is destructed, it is responsible for destructing any
    "sub-expressions" (its lhs or rhs) if it has them (Plus, Minus, Times, 
    and Div Expressions). In other words, you need to write the appropriate destructors.

 4. The toString function should return a string representation of the
    Expression in infix notation. That is, if the input is "(+ 4 5)" it should
    return "(4 + 5)".  Rather than taking on operator precedence rules in this assignment, 
    we will place parenthesis around the expressions for Plus, Minus, Times, and Div.
    For example, "(+ (+ 4 5) 7)" will result in "((4 + 5) + 7)"

 5. You need to declare your classes in `expr.hpp`.  You can implement the
    methods inside the class (i.e., in `expr.hpp`), or you can implement them in `expr.cpp`.

 6. All three parts contain sample_input.txt and sample_out.txt, which show the
    various inputs and respective outputs that should be generated.
    
    The third part includes invalid_inputs.txt and invalid_output.txt, which show
    some invalid inputs (which the parser handles) and the resulting output.
    Note that the parser handles the error cases here, but you should make sure
    that you do not leak memory on the invalid_inputs.txt when the 
    parser cleans up. As long as the destructors are correctly written, this should not 
    be a problem.

## Hints
Some possibilities that you may wish to include in your implementation but are not necessary. 
It may be useful to discuss these with your fellow students, TAs, or your instructor.

  - Implement the Expression class as abstract, and all of the functions in it are abstract.

  - Place one or more abstract classes in the inheritance hierarchy.
    This class has some fields which would otherwise appear in each of its subclasses. 
    This class adds one more abstract method, which is used in the `toString` implementation.
    With this approach, implement `toString` in this class, and avoid overriding it in
    any of its subclasses.

  - A PlusExpression would evaluate itself by evaluating its lefthand side,
    evaluating its right-hand side, and then adding the two results together
    to get its answer.

  - Think about how your objects will get destructed. Note that 
    the static type of pretty much everything in the parsing/printing code
    is Expression * 

  - [stringstream](https://cplusplus.com/reference/sstream/stringstream/stringstream/) is very nice for implementing `toString()` or simply use string concatenation.

## Submission
Once you have tested and validated the functionality for part 1, 
submit `expr.cpp` and `expr.hpp` to Gradescope.
