# Point
For this problem, you will write a "Point" class in `point.hpp` and
`point.cpp`. The Point class will represent a 2-D point (i.e., it has an
_x_ and a _y_ coordinate). The class should have fields for the _x_ and _y_,
which should be private doubles.

The Point class must have the following public functionality:
  - A default constructor, which initializes the point's x and y to 0. 
  - The method

    `void move(double dx, double dy);`

    which increases the point's x by dx, and its y by dy.
  - The method

    `double distanceFrom(const Point & p);`

    which takes a constant reference to another point and computes the distance between the two points
    using the [Pythagorean_theorem](https://en.wikipedia.org/wiki/Pythagorean_theorem).
    
`main.cpp` contains the application's main function and uses your Point class. Specifically, it reads input from `stdin` (`cin`), where the first line tells it how many Points to create. It then reads one
command per line until end of input (can be specified in the terminal by `ctrl-d`). Commands one of the follow two possibilities:
  - m pnum dx dy
  - d p1 p2

The first moves the point specified by pnum (an int) by
<dx,dy> (doubles). The second prints the distance between the
points specified by p1 and p2 (ints).

Study how main.cpp works - the code demonstrates various tasks that will be useful for the Fintech 510 class.

We have already provided a sample input (input1.txt), sample output (output1.txt), and a makefile.

Once your program produces the correct output for input1.txt, submit `point.cpp` and `point.hpp` to Gradescope.
