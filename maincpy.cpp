#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions.

  cout << "============= Pre-supplied functions =============" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  /*Question1 checks
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

*/
  //  Question 2 checks
  /*

  cout << "=================== Question 2 ===================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // write more tests
  cout << "Putting '9' into A7 is ";
  if (!make_move("A7", '9', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << "Putting 'b' into A7 is ";
  if (!make_move("A7", 'b', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << "Putting '1' into AA is ";
  if (!make_move("AA", '9', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << "checking all_checks function" << endl;
  cout << "Putting '1' into B3 is ";
  if (all_checks(1,2,'1',board))
    cout << "VALID" << endl;
  else
    cout << "NOT VALID" << endl;
  cout << "Putting '3' into B3 is ";
  if (all_checks(1,2,'1',board))
    cout << "VALID" << endl;
  else
    cout << "NOT VALID" << endl;

  cout << "text count using all_checks function" << endl;
  int count = 0;
  for (char k = '1'; k <= '9'; k++)
  {
    if (all_checks(1, 2, k, board))
    {
      count++;
      cout << "count = " << count << " because of " << k << endl;
      //flag = k;
    }
  }

*/


  /*Question 3 checks*/ /*
  cout << "=================== Question 3 ===================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  */
  cout << "=================== Question 4 ===================" << endl << endl;
/*
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;
*/
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  } else {
    cout << "A solution cannot be found." << endl;
    display_board(board);}
  cout << endl;

	// write more tests


  /*
  cout << "=================== Question 5 ===================" << endl << endl;
  */
	// write more tests

  return 0;
}
