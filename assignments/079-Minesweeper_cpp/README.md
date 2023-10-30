# Minesweeper - C++
This assignment repeats another Python assignment, but the source
code has been updated for C++ and takes advantage of classes in C++.

If you are not familiar with the game of minesweeper, you might take 
a minute to read up about it on the internet 
(https://en.wikipedia.org/wiki/Minesweeper_(video_game),
 but you don't need much game expertise to do this assignment.

The distribution contains an almost working version of the code, except 
that you will need to write code for the constructor, desctructor, and two
other methods:
```c++
Board(int w, int h, int numMines): width{w}, height{h}, totalMines{numMines}
~Board()
int countMines(int x, int y)
bool checkWin()
```

## Constructor
The constructor must allocate memory for a 2-dimensional array (matrix) of
Square objects. It then needs to call `addRandomMine()` an appropriate 
number of times (i.e., `numMines`) to "randomly" place mines on the board.

Notes:
- You must initialize your board before starting to call `addRandomMine()`.
- The mine generation is pseudo-random and will not change if you re-run 
  the program multiple times with the same parameters.
- The board should be constructed such that is indexed as `board[y][x]`   
   where y is between 0 and the height and x is between 0 and the width.

## Destructor
The destructor frees any memory allocated by the constructor.

## countMines()
This method takes an (x,y) coordinate. It should count the mines in the 
8 squares around that (x,y) coordinate and returns that count.  
The `Square` class contains a behavior (a method) in `has_mine()` that
returns `true` if a square has a mine or `false` otherwise. Ensure 
you pay careful attention to the bounds of the board.

## checkWin()
Check if the game has been won, which is identified by the situation
when no squares are UNKNOWN.

Note: You should NOT change any of the other provided methods!

Once you have these all working, you should have a playable game of 
minesweeper.  Note that there are a few differences in gameplay
from the "standard" game:
 - Select a square by entering its x (column) and y (row) coordinate.
   The `x` coordinates are listed across the top and the `y` are listed
   down the left side to reduce counting.
 - The game will automatically figure out the "obvious" squares:
   both mines and non-mined spaces.  It will reveal these to you 
   as soon as it considers them trivial to figure out.   
 - You cannot manually mark a square that you suspect has a mine

Once your code is complete and verified, submit `minesweeper.cpp` 
to the Gradescope assignment.

