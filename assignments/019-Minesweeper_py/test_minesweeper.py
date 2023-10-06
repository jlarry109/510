import minesweeper
import random 
random.seed(42)   # do this for repeatability
board = minesweeper.make_board(4,5,10)
print(board)
minesweeper.print_board(board)
print(minesweeper.board_height(board))
print(minesweeper.board_width(board))
print(minesweeper.count_mines(board, 3, 4))