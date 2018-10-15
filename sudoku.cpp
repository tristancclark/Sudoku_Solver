#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/* Question 1 - boolean function that takes a 9 x 9 array of
 characters representing a Sudoku board and returns true if
 all the board positions are occupied by digits and false otherwise. */

bool is_complete(char board[9][9]){

  for (int i = 0; i < 9; i++)
  {
      for(int j = 0; j < 9; j++)
      {
	if(!isdigit(board[i][j]))
	  return false;
      }
  }
  return true;
}

/* End of is_complete function*/

/* Question 2 - places a digit on a position on a Sudoku board.
Here digit is a integer between 0 and 9. Position (where the digit is placed) is a two
 character string, the first character denotes the row (A-I) and the second character denotes
the column (1-9). The board must be a 2-dimensional character array of 9 x 9. */

bool make_move(char position[2], char digit, char board[9][9]){

  /* Check if a valid digit is entered. */
  if (digit > '9' || digit < '0')
  {
    cerr << endl << "(Error: This Sudoku puzzle only allows integers from 0 - 9.)" << endl;
    return false;
  }

  /*Check if a valid position is entered*/

  if (islower(position[0]))
    position[0] += ('A'-'a');
  if (position[0] > 'I' || position[0] < 'A')
  {
    cerr << endl << "(Error: This Sudoku puzzle only has rows from A to I.)" << endl;
    return false;
  }
  if (position[1] > '9' || position[1] < '0')
  {
    cerr << endl << "(Error: This Sudoku puzzle only has columns from 0 to 9.)" << endl;
    return false;
  }

  /*Place digit in position*/

  board[static_cast<int>(position[0])-'A'][position[1]-'1'] = digit;
  return true;
}
