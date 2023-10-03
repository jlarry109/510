Read Expressions:

1. Create a file "answer.txt".
2. Execute the code in code.cpp by hand as demonstrated with
   the memory/trace diagrams in class. 
   Write the output in your "answer.txt" file
3. Take a picture of your diagram.
4. Compile the program by using the provided Makefile.  
   (The C++ retirement assignment discussed how to do this.)
5. Execute the program: `./test`
6. Compare the output to your expected output.  Make any corrections.
7. Submit answer.txt and your diagram (this can be png/jpg/pdf) to Gradescope.

**Notes:**

`Something(int _x): x(_x)` is a constructor that is called when a new 
instance of Something is created. This constructor initializes the state 
of the object, contained in the variable x to the parameter `_x`

`~Something()` is a destructor that is called when an object goes out of 
scope or a programmer explicitly destroys an object with the `delete` keyword.

```c++
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>

class Something
{
  int x;

public:
  Something(int _x) : x(_x)
  {
    std::cout << "Something(" << x << ")\n";
  }
  ~Something()
  {
    std::cout << "~Something(" << x << ")\n";
  }
};

int g(int a, int b)
{
  Something(99);
  int divisor = a + b;
  if (divisor == 0)
  {
    throw std::domain_error("Division by zero");
  }
  return (a - b) / (divisor);
}

int f(int x)
{
  int total = 0;
  Something(42);
  for (int i = 37; i <= 42; i++)
  {
    total += g(x, i);
  }
  return total;
}

int main(void)
{
  Something s1(1);
  try
  {
    Something s2(7);
    Something(3); // read this line carefully.....
    int answer = f(-40);
    std::cout << "The answer is " << answer << "\n";
  }
  catch (std::out_of_range &re)
  {
    std::cout << "A range exception (" << re.what() << ") occured!\n";
  }
  catch (std::domain_error &de)
  {
    std::cout << "A domain error (" << de.what() << ") occured!\n";
  }
  catch (std::exception &e)
  {
    std::cout << "An exception (" << e.what() << " ) occured!\n";
  }
  std::cout << "At the end of main \n";
  return EXIT_SUCCESS;
}
```