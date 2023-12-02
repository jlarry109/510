// This program builds and solves text-based mazes
// By: Chris Gregg
// Date: October 16, 2016
// The maze creation code was modified from:
// http://azerdark.wordpress.com/2009/03/29/588/
// and http://www.mazeworks.com/mazegen/mazetut/index.htm
// Modified by John Slankas, November 2023 
// to make generic to C++ Standard Libraries without
// requiring additional class files / libraries, some
// code simplifications as well.

#include <iostream>
#include <vector>
#include <string>

using std::string, std::vector, std::cout;

const int MAXCELL = 900; // 30 x 30
const char WALL = 'X';
const char PATH = ' ';

typedef std::vector<std::vector<char>> Grid;

// prototypes
void initMaze(Grid &maze);

// generate maze
void generateMaze(Grid &maze, int sideLength);
void mazeGenerator(int index, int backtrackX[],
        int backtrackY[], int x, int y, int n, int visited, Grid &grid);
bool isClosed(int x, int y, Grid &maze);

// solve maze
void solveMazeRecursive(Grid &maze);
bool solveMazeRecursive(Grid &maze, int row, int col);

void printMaze(Grid &maze);

int convertStringToInt(std::string s) {
    std::size_t idx = 0;
    int result = std::stoi(s,&idx);
    if (idx != s.size()) {
        throw std::invalid_argument("unprocessed input: "+s);
    }
    return result; 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " size\n";
        return EXIT_FAILURE;
    }

    int sideLength = -1;
    try {
        sideLength = convertStringToInt(argv[1]);
    }
    catch (const std::exception& ex) {
        std::cerr << "Unable to get get size of the maze: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }
    if (sideLength < 2 || sideLength > 30) {
        std::cerr << "Invalide size for maze.  Must be between 2 and 30\n";
        return EXIT_FAILURE;
    }

    Grid maze(sideLength * 2 + 1, std::vector<char>(sideLength * 2 +1));  // * 2 + 1 accounts for the walls

    initMaze(maze);
    generateMaze(maze, sideLength);

    cout << "Original Maze:\n";
    printMaze(maze);

    solveMazeRecursive(maze);

    cout << "Solved Maze:\n";
    printMaze(maze);
    return 0;
}

void printMaze(Grid &maze) {
    for (size_t row = 0U; row < maze.size(); row++) {
        for (size_t col = 0U; col < maze[row].size(); col++) {
            cout << maze[row][col];
        }
        cout << std::endl;
    }
    cout << std::endl;
}


void solveMazeRecursive(Grid &maze) {
    solveMazeRecursive(maze,1,1);  // start solving the maze at the start
    maze[1][1] = 'S'; // replace start, which may be removed during solving stage
}

bool solveMazeRecursive(Grid &maze, int row, int col) {
    // Only alter this function
    // Base case: if we reached the finish cell, return true
    if (maze[row][col] == 'F') {
        return true;
    }

    // If the current cell is a wall or has already been visited, return false
    if (maze[row][col] == 'X' || maze[row][col] == '.' || maze[row][col] == 'b') {
        return false;
    }

    // Mark the current cell as visited
    maze[row][col] = '.';

    // Try moving in all four directions: up, down, right, left
    if (solveMazeRecursive(maze, row - 1, col) ||    // up
        solveMazeRecursive(maze, row + 1, col) ||    // down
        solveMazeRecursive(maze, row, col + 1) ||    // right
        solveMazeRecursive(maze, row, col - 1)) {    // left
        return true;
    }

    // If none of the paths lead to the finish, backtrack
    maze[row][col] = 'b';  // mark as backtracked
    return false; // only present so initial code will compile
}



void initMaze(Grid &maze) {
    for (size_t row = 0; row < maze.size(); row++)  {
        for (size_t col = 0; col < maze[row].size(); col++) {
            if (row % 2 == 0 || col % 2 == 0) {  maze[row][col] = WALL; }
            else {  maze[row][col] = PATH;  }
        }
    }
}

// generates a maze
void generateMaze(Grid &maze, int sideLength) {
    int index = 0;
    int backtrackX[MAXCELL];
    int backtrackY[MAXCELL];
    backtrackX[index] = 1;
    backtrackY[index] = 1;
    mazeGenerator(index, backtrackX, backtrackY, 1, 1, sideLength, 1, maze);
    maze[1][1]='S'; // the start location
    maze[maze.size()-2][maze.size()-2] = 'F';  // Finish location
}

void mazeGenerator(int index, int backtrackX[], int backtrackY[],
        int x, int y, int n, int visited, Grid &maze) {
    if (visited < n * n) {
        int neighbourValid = -1;
        int neighbourX[4];
        int neighbourY[4];
        int step[4];

        int xNext;
        int yNext;

        if (x - 2 > 0 && isClosed(x - 2, y,maze)) {  // upside
            neighbourValid++;
            neighbourX[neighbourValid]=x - 2;;
            neighbourY[neighbourValid]=y;
            step[neighbourValid]=1;
        }

        if (y - 2 > 0 && isClosed(x, y - 2, maze)) { // leftside
            neighbourValid++;
            neighbourX[neighbourValid]=x;
            neighbourY[neighbourValid]=y - 2;
            step[neighbourValid]=2;
        }

        if (y + 2 < n * 2 + 1 && isClosed(x, y + 2, maze)) {  // rightside
            neighbourValid++;
            neighbourX[neighbourValid]=x;
            neighbourY[neighbourValid]=y + 2;
            step[neighbourValid]=3;
        }

        if (x + 2 < n * 2 + 1 && isClosed(x + 2, y, maze)) {  // downside
            neighbourValid++;
            neighbourX[neighbourValid]=x+2;
            neighbourY[neighbourValid]=y;
            step[neighbourValid]=4;
        }

        if (neighbourValid == -1) {
            // backtrack
            xNext = backtrackX[index];
            yNext = backtrackY[index];
            index--;
        }

        if (neighbourValid!=-1)  {
            int randomization = neighbourValid + 1;
            int random = rand()%randomization;
            xNext = neighbourX[random];
            yNext = neighbourY[random];

            index++;
            backtrackX[index] = xNext;
            backtrackY[index] = yNext;

            int rstep = step[random];

            if (rstep == 1)
                maze[xNext+1][yNext] = PATH;
            else if (rstep == 2)
                maze[xNext][yNext + 1] = PATH;
            else if (rstep == 3)
                maze[xNext][yNext - 1] = PATH;
            else if (rstep == 4)
                maze[xNext - 1][yNext] = PATH;
            visited++;
        }

        mazeGenerator(index, backtrackX, backtrackY,xNext,yNext, n, visited, maze);
    }
}




bool isClosed(int x, int y, Grid &maze) {
    if (maze[x - 1][y] == WALL && maze[x][y - 1] == WALL && 
        maze[x][y + 1] == WALL && maze[x + 1][y] == WALL)
        return true;
    else 
        return false;
}