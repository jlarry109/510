# Maze Runner

For this assignment, you have been placed into a maze in the top left 
corner and must escape by finding your way to the finish in the
bottom right corner.  As with any maze, walls and dead-ends block the 
Intrepid adventurer's path.  You'll need to use recursion and backtracking
to survive.
```
XXXXXXXXXXXXXXXXXXXXX
XSX                 X
X X XXXXXXXXXXXXXXX X
X X   X X     X   X X
X XXX X X XXX X X X X
X X     X   X   X   X
X XXXXX XXX XXXXXXXXX
X     X   X         X
XXXXX XXX XXXXXXXXX X
X     X X X       X X
X XXXXX X X XXXXX X X
X X       X X   X X X
X XXX XXXXX XXX X X X
X   X     X X   X   X
XXX XXXXXXX X XXXXX X
X   X       X X   X X
X XXX XXXXXXX X X X X
X X     X     X X   X
X XXXXX X XXX X XXXXX
X       X   X      FX
XXXXXXXXXXXXXXXXXXXXX
```


In the distribution folder, two files have been provided:
1. __maze.cpp__ provides code to generate random mazes and print those
   mazes.  You'll "just" need to implement
   ```c++
   bool solveMazeRecursive(Grid &maze, int row, int col);
   ```
2. __Makefile__ generates the maze executable.

To execute the program, use
```
./maze sizeOfMaze
```

As you navigate the maze, leave a period `.` behind to mark your 
trail. When you backtrack from a location, place a `b` on the cell so you'll 
know not to go back to that location.  You do not have magic powers and thus 
are blocked by walls.


You should evaluate paths in this order: up, down, right, left  (north, south, 
east, west). The "escape" cell is marked with an "F".  Remember that 0,0 
represents the top left while size-1,size-1 represents the bottom right. Rows 
are specified first and then columns.  Subtract 1 from a row to move up (north)
while add 1 to move down (south).  Add 1 to a column to move right (east) and 
substract 1 from a column to move left (west). Note that the maze is surrounded
by a wall so you should not need to check boundaries. The solved maze should be
printed as - 
```
XXXXXXXXXXXXXXXXXXXXX
XSXbbbbbbbbbbbbbbbbbX
X.XbXXXXXXXXXXXXXXXbX
X.XbbbXbXbbbbbXbbbXbX
X.XXXbXbXbXXXbXbXbXbX
X.XbbbbbXbbbXbbbXbbbX
X.XXXXXbXXXbXXXXXXXXX
X.....XbbbXbbbbbbbbbX
XXXXX.XXXbXXXXXXXXXbX
X.....XbXbX.......XbX
X.XXXXXbXbX.XXXXX.XbX
X.XbbbbbbbX.X   X.XbX
X.XXXbXXXXX.XXX X.XbX
X...XbbbbbX.X   X...X
XXX.XXXXXXX.X XXXXX.X
X...X.......X X...X.X
X.XXX.XXXXXXX X.X.X.X
X.X  ...X     X.X...X
X.XXXXX.X XXX X.XXXXX
X.......X   X  ....FX
XXXXXXXXXXXXXXXXXXXXX
```

Remember that you'll have multiple base case - one implies success 
(reaching `F`) while others (running into a wall, a previous path) are failures.
As with Eight Queens, Sudoku, and generating permutations, you will need
to evaluate multiple paths at a particular cell.

You should not modify any other code than `solveMazeRecursive()`.

Once you have succesfully escaped the maze, submit `maze.cpp` to the 
Gradescope assignment.
