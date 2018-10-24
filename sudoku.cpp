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

/* Question 1 - Function that returns true if all the board positions
are occupied by digits and false otherwise. */

bool is_complete(const char board[9][9])
{
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

/* Question 2 - Function that checks if a move is valid.
Returns true if move is valid and implements the move.
Returns false if the move, the position or the digit are invalid. */

bool make_move(const char* position, char digit, char board[9][9])
{
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

/*Helper function to check for the existance of a digit in a row.
Returns true if no digit exists and false otherwise. */

bool row_check(int row, char digit, const char board[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    if (board[row][i] == digit)
      return false;
  }
  return true;
}

/*Helper function to check for the existance of a digit in a column.
Returns true if no digit exists and false otherwise. */

bool column_check(int column, char digit, const char board[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    if (board[i][column] == digit)
      return false;
  }
  return true;
}

/*Helper function to check for the existance of a digit in the block that
row and column intercept.
Returns true if no digit exists and false otherwise. */

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

/*Helper function to check for the existance of a digit in a row, column and the
block that row and column intercept.
Returns true if no digit exists in any and false otherwise.*/

bool all_checks(int row, int column, char digit, const char board[9][9])
{
  if (row_check(row, digit, board) && column_check(column, digit, board) && block_check(row, column, digit, board))
    return true;
  return false;
}

/*Question 3 - Function to copy a 9 x 9 character array to a text file called filename.
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
      if (!isdigit(board[i][j]) && board[i][j] != '.') //check for valid character
      {
        cerr << "Contains an invalid character!" << endl;
        return false;
      }
      out_stream << board[i][j]; //output character to file

      if (out_stream.fail()) //check for failure
      {
        out_stream.close();
        cerr << "File error occured." << endl;
        return false;
      }
    }
    out_stream << endl;
  }
  out_stream.close();
  return true;
}

/*Question 4 - Function to solve a 9 x 9 partially completed sudoku board.
Returns true and the solved board if solving the board is possible.
Returns false if solving the board is not possible. */

bool solve_board(char board[9][9])
{
  int row, column;
  char current_digit = '1';

  if (is_complete(board)) //check if board is complete
    return true;

  find_first_empty_box(row, column, board);

  do
  {
    if (!find_first_valid_digit(row, column, current_digit, board)) //check if no valid digit fits
    {
      board[row][column] = '.';
      return false;
    }

    board[row][column] = current_digit;

  } while(!solve_board(board));

  return true;
}

/*Helper function that scans each row from left to right searching for an empty box.
Returns the position of first box found as the arguments row and column.*/

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

/*Helper function that finds the lowest possible 'potentially' valid digit and
changes the argument current_digit to equal this.
Returns true if a valid digit was found.
Returns false if no valid digit was found. */

bool find_first_valid_digit(int row, int column, char &current_digit, char board[9][9])
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
