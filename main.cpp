#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "=================== Question 1 ===================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "=================== Question 2 ===================" << endl << endl;

  load_board("easy.dat", board);

  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board))
    cout << "NOT a valid move" << endl << endl;
  else
  {
    cout << "is a valid move. The board is:" << endl;
    display_board(board);
    cout << endl;
  }

  cout << "Putting '6' into E5 is ";
  if (!make_move("E5", '6', board))
    cout << "NOT a valid move" << endl << endl;
  else
  {
    cout << "is a valid move. The board is:" << endl;
    display_board(board);
    cout << endl;
  }

  cout << "Putting 'a' into E5 is ";
  if (!make_move("E5", 'a', board))
    cout << "NOT a valid move" << endl << endl;
  else
  {
    cout << "is a valid move. The board is:" << endl;
    display_board(board);
    cout << endl;
  }

  cout << "Putting '7' into E56 is ";
  if (!make_move("E56", '7', board))
    cout << "NOT a valid move" << endl << endl;
  else
  {
    cout << "is a valid move. The board is:" << endl;
    display_board(board);
    cout << endl;
  }

  cout << "Putting '7' into Z7 is ";
  if (!make_move("Z7", '7', board))
    cout << "NOT a valid move" << endl << endl;
  else
  {
    cout << "is a valid move. The board is:" << endl;
    display_board(board);
    cout << endl;
  }

  cout << "Putting '7' into AB is ";
  if (!make_move("AB", '7', board))
    cout << "NOT a valid move" << endl << endl;
  else
  {
    cout << "is a valid move. The board is:" << endl;
    display_board(board);
    cout << endl;
  }


  cout << "=================== Question 3 ===================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << "=================== Question 4 ===================" << endl << endl;

  clock_t t;
  double time_taken;

  load_board("easy.dat", board);
  t = clock();
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    t = clock() - t;
    display_board(board);
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    cout << "Time taken to solve this puzzle: " << time_taken*1000 << " milliseconds" << endl;
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);
  t = clock();
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    t = clock() - t;
    display_board(board);
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    cout << "Time taken to solve this puzzle: " << time_taken*1000 << " milliseconds" << endl;
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;


  cout << "=================== Question 5 ===================" << endl << endl;

  load_board("mystery1.dat", board);
  t = clock();
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    t = clock() - t;
    display_board(board);
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    cout << "Time taken to solve this puzzle: " << time_taken*1000 << " milliseconds" << endl;
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("mystery2.dat", board);
  t = clock();
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    t = clock() - t;
    display_board(board);
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    cout << "Time taken to solve this puzzle: " << time_taken*1000 << " milliseconds" << endl;
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("mystery3.dat", board);
  t = clock();
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    t = clock() - t;
    display_board(board);
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    cout << "Time taken to solve this puzzle: " << time_taken*1000 << " milliseconds" << endl;
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  return 0;
}
