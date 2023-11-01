
#include <assert.h>
#include <limits>

#include <iostream>
#include <iomanip>
using namespace std;

enum ClickType {CLICK_KNOWN_MINE, CLICK_INVALID, CLICK_CONTINUE, CLICK_LOSE };

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

int readInteger() {
    int value;
    while (!(std::cin >> value)) {
        if (std::cin.eof()) {
            cerr << "End of file from keyboard reading a number.  Quitting\n";
            exit(EXIT_FAILURE);
        }
        
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
        std::cout << "You did not enter any valid number\n" <<
                 "Please try again\n";
    }
    
    return value;
}

class Square {
private:
    int square = UNKNOWN;
    
public:
    Square() {}

    void assign_mine()       { square = HAS_MINE;    }
    void setCount(int count) { square = count;  }
    void mark_known_mine()   { square = KNOWN_MINE;}

    bool is_mine()        { return (square == HAS_MINE || square == KNOWN_MINE);  }
    bool known_mine()     { return square == KNOWN_MINE;   }
    bool has_mine()       { return square == HAS_MINE; }
    bool is_unknown()  { return square == UNKNOWN; }
    int count() {return square; }

   ClickType click (int surroundingMineCount) {

      if (known_mine()) {  // don't allow the player to kill themselves
          return CLICK_KNOWN_MINE;
      }
      if (has_mine()) {
          return CLICK_LOSE;
      }
      if (square >= 0) {  // they've already know this answer
          return CLICK_CONTINUE;
      }
      // no mine here, so show the player the number of mines around this square
      setCount(surroundingMineCount);

      return CLICK_CONTINUE;
  }

};

ostream &operator<<(ostream &out, Square s) {
    if      (s.known_mine())                 { cout << "*"; }  
    else if (s.has_mine() or s.is_unknown()) { cout << "?"; }
    else {
        int mine_count = s.count();
        if (mine_count == 0) { cout << " ";   }
        else { cout << mine_count; }
    }
    return out;
}


class Board {
private:
    Square **board;
    const int width;
    const int height;
    const int totalMines;

    bool in_bounds(int x, int y) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

public:
  Board(int w, int h, int numMines): width{w}, height{h}, totalMines{numMines} {
      /* write code*/
  }

  ~Board() {
      /* write code*/
  }

  void addRandomMine() {
      int x;
      int y;
      // we could have a board too small for the number of requested mines.
      // try w*h*10 times before giving up
      int limit = width * height * 10;
      do {
          x = random() % width;
          y = random() % height;
          limit--;
      } while(board[y][x].has_mine() && limit > 0);
      board[y][x].assign_mine();
  }


  int countMines(int x, int y) {
      /* write code*/
  }

  bool checkWin() {
      /* write code*/
  }

  int countKnownMines() {
      int count = 0;
      for (int x =0; x < height; x++) {
          for (int y = 0; y < width; y++) {
              if (board[x][y].known_mine()) {
                  count++;
              }
          }
      }
      return count;
  }
	
  void printBoard() {
      cout << "    ";
      for (int x = 0; x < width; x++) { cout << x/10;  } cout << "\n    ";
      for (int x = 0; x < width; x++) { cout << x%10;  } 
      cout << "\n";
	  
      cout << "----";
  	  for (int x = 0; x < width; x++) { cout << "-";  }
	  cout << "\n";

	  for (int y = 0; y < height; y++) {
	      cout << setw(2) <<  y%100 << ": ";
	      for (int x = 0; x < width; x++) {
              cout << board[y][x];
	      }
	      cout << "\n";
	  }
      
      cout << "----";
	  for (int x = 0; x < width; x++) { cout << "-";  }
	  cout << "\n";

	  cout << "    ";
	  for (int x = 0; x < width; x++) { cout << x/10;  } cout << "\n    ";
  	  for (int x = 0; x < width; x++) { cout << x/10;  }

	  cout << "\nFound " << countKnownMines() << " of " << totalMines << " mines\n";
  }

  void doReveal(int x, int y, int revealMines){
      for (int dy = -1; dy <=1 ; dy++) {
          for (int dx = -1; dx <=1 ; dx++) {
              int nx = x + dx;
              int ny = y + dy;
              if (in_bounds(nx,ny)) {
                  if (revealMines) {
                      //assert(board[ny][nx].square != UNKNOWN);
                      if (board[ny][nx].has_mine()){
                          board[ny][nx].mark_known_mine();
                      }
                  }
                  else  {
                      //assert(board[ny][nx].square != HAS_MINE);
                      if (board[ny][nx].is_unknown()) {
                          board[ny][nx].setCount(countMines(nx,ny));
                      }
                  }
              }
          }
      }
  }

  int maybeReveal(int x, int y) {
      int unknownSquares = 0;
      int knownMines = 0;
      for (int dy = -1; dy <=1 ; dy++) {
          for (int dx = -1; dx <=1 ; dx++) {
              int nx = x + dx;
              int ny = y + dy;
              if (in_bounds(nx,ny)) {
                  if (board[ny][nx].is_unknown()||
                      board[ny][nx].has_mine()) {
                      unknownSquares++;
                  }
                  else if(board[ny][nx].known_mine()) {
                      knownMines++;
                  }
              }
          }
    }
    assert(knownMines + unknownSquares >= board[y][x].count());
    assert(knownMines <= board[y][x].count());
    if (unknownSquares > 0) {
        int revealMines = (knownMines + unknownSquares == board[y][x].count());
        int allKnown = knownMines == board[y][x].count();
        if (revealMines || allKnown) {
            assert(!revealMines || !allKnown);
            doReveal(x,y, revealMines);
            return 1;
        }
    }
    return 0;
  }

  void determineKnownMines() {
      int foundMore = 0;
      for (int y = 0; y < height; y++) {
          for (int x = 0; x < width; x++) {
              if (board[y][x].count() >= 0) {
                  foundMore = maybeReveal(x,y) || foundMore;
              }
          }
      }
      if (foundMore) {
          determineKnownMines();
      }
  }

  void revealMines() {
      for (int y = 0; y < height; y++) {
          for (int x = 0; x < width; x++) {
              if (board[y][x].has_mine()) {
                  board[y][x].mark_known_mine();
              }
          }
      }
  }

  /**
   * returns true if the game is not over
   */
  bool playTurn() {
      cout << "Current board:\n";
      printBoard();
      cout << "x coordinate:\n";
      int x = readInteger();
      cout << "y coordinate:\n";
      int y = readInteger();

      if (!in_bounds(x,y)) {
          cout << "That is not a valid square, please try again\n";
      }
      else {
          ClickType result = board[y][x].click(countMines(x,y));
          determineKnownMines();
          if (result == CLICK_LOSE) {
              cout << "Oh no! That square had a mine. You lose!\n";
              revealMines();
              printBoard();
              return false;
          }
          else if (result == CLICK_KNOWN_MINE) {
              cout << "You already know there is a mine there!\n";
          }
          else if(checkWin()) {
              printBoard();
              cout << "You win!\n";
              return false;
          }
      }
      return true;
  }

  void playGame() {
      while (playTurn()) {
            ; // nothing to do, playTurn has all of the work, returns false when game over
      }
  }

};

bool checkPlayAgain() {
    string answer;
    cout << "Do you want to play again?\n";
    if (cin >> answer) {
        if (answer.length() > 0 && (answer[0] == 'Y' || answer[0] == 'y')) {
          return true;
        }
    }
    return false;
}

int main(int argc, char ** argv) {
    if (argc != 4) {
        cerr << "Usage: minesweeper width height numMines\n";
        return EXIT_FAILURE;
    }

    try {
        int width    = stoi(argv[1]);
        int height   = stoi(argv[2]);
        int numMines = stoi(argv[3]);
        if (width <= 0 || height <= 0 || numMines <= 0) {
            throw new std::invalid_argument("bad values");
        }

        do {
            Board b = Board(width, height, numMines);
            b.playGame();
        } while (checkPlayAgain());
    }
    catch(std::invalid_argument &a) {
       cerr << "Width, height, and numMines must all be positive ints\n";
       return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
