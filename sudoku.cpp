#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include <cstring>
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

  cout << ((row == 9) ? "Success!" : "Failed!");
  cout << endl;
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

bool is_complete(const char board[9][9]){

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

/* Question 2 - places a digit on a position on a Sudoku board.
Here digit is a integer between 0 and 9. Position (where the digit is placed) is a two
 character string, the first character denotes the row (A-I) and the second character denotes
the column (1-9). The board must be a 2-dimensional character array of 9 x 9. */

bool make_move(const char* position, char digit, char board[9][9]){

  if (digit > '9' || digit < '0') //check for valid digit
  {
    cerr << endl << "(Error: This Sudoku puzzle only allows integers from 0 - 9.)" << endl;
    return false;
  }

  if (strlen(position) > 2) //check for valid position length
  {
    cerr << endl << "(Error: This Sudoku puzzle is 2-D, please enter a two digit position.)" << endl;
    return false;
  }

  if (position[0] > 'I' || position[0] < 'A') //check for valid row
  {
    cerr << endl << "(Error: This Sudoku puzzle only has rows from A to I.)" << endl;
    return false;
  }

  if (position[1] > '9' || position[1] < '0') //check for valid column
  {
    cerr << endl << "(Error: This Sudoku puzzle only has columns from 0 to 9.)" << endl;
    return false;
  }

  if (all_checks(position[0] - 'A', position[1] - '1', digit, board)) //check if valid move
  {
    board[position[0]-'A'][position[1]-'1'] = digit; //place digit
    return true;
  }
  return false;
}

/*Function to check for a duplicate in the row that the position exists in.
Returns true if no duplicate exists and false otherwise. */

bool row_check(int row, int column, char digit, const char board[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    if (board[row][i] == digit)
      return false;
  }
  return true;
}

/*Function to check for a duplicate in the column that the position exists in.
Returns true if no duplicate exists and false otherwise. */

bool column_check(int row, int column, char digit, const char board[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    if (board[i][column] == digit)
      return false;
  }
  return true;
}

/*Function to check for a duplicate in the block that the position exists in.
Returns true if no duplicate exists and false otherwise. */

bool block_check(int row, int column, char digit, const char board[9][9])
{
  int block_row = row/3; //initialise block row & column numbers from 0-2.
  int block_column = column/3;

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (board[block_row*3+i][block_column*3+j] == digit)
      return false;
    }
  }
  return true;
}

/*Function to check for duplicates in row, column and block.
Returns true if no duplicates in any and false otherwise.*/
bool all_checks(int row, int column, char digit, const char board[9][9])
{
  if (row_check(row, column, digit, board) && column_check(row, column, digit, board) && block_check(row, column, digit, board))
    return true;
  return false;
}

/*Question 3 - Takes a 9 x 9 character array and copy to a text file called filename.
Returns true if copy was successful.
Returns false if a unexpected character was found or an error occured.*/

bool save_board(const char* filename, const char board[9][9])
{
  ofstream  out_stream;
  out_stream.open(filename);

  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (!isdigit(board[i][j]) || board[i][j] == '.') //check for valid character
        return false;

      out_stream << board[i][j]; //output character to file

      if (out_stream.fail()) //check for failure
      {
        out_stream.close();
        return false;
      }
    }
    out_stream << endl;
  }
  out_stream.close();
  return true;
}

/*Question 4 - Takes a 9 x 9 partially completed sudoku board.
If solving the board is possible then it returns true and the solved board.
If solving the board is not possible then it returns false. */

bool solve_board(char board[9][9])
{
  static int level = 0;
  level++;
  cout << "RECURSION LEVEL: " << level << endl;

  int row, column;
  char current_digit = '1';

  if (is_complete(board)) //check if board is complete
    return true;

  find_first_empty_box(row, column, board);

  do
  {
    if (!first_valid_digit(row, column, current_digit, board)) //check if no valid digit fits
    {
      board[row][column] = '.';
      return false;
    }

    board[row][column] = current_digit;

  } while(!solve_board(board));

  return true;
}

/*Function that scans each row from left to right searching for an empty box.
Returning the position of first box found as the arguments row and column.*/
void find_first_empty_box(int &row, int &column, const char board[9][9])
{
  for (int i = 0; i < 9; i++) //for each row
  {
    for (int j = 0; j < 9; j++) //for each column
    {
      if (board[i][j] == '.')
      {
        row = i;
        column = j;
        return;
      }
    }
  }
  cout << "Sudoku board is already full, no empty boxes found!" << endl;
}

/*Function that finds the lowest possible 'potentially' valid digit and
changes the argument current_digit to equal this.
Function will return true if a valid digit was found.
Function will return false if no valid digit was found. */
bool first_valid_digit(int row, int column, char &current_digit, char board[9][9])
{
  for (; current_digit <= '9'; current_digit++)
  {
    if (all_checks(row, column, current_digit, board))
    {
      return true;
    }
  }
  return false;
}
