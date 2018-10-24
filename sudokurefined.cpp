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

/* End of is_complete function*/

/* Question 2 - places a digit on a position on a Sudoku board.
Here digit is a integer between 0 and 9. Position (where the digit is placed) is a two
 character string, the first character denotes the row (A-I) and the second character denotes
the column (1-9). The board must be a 2-dimensional character array of 9 x 9. */

bool make_move(const char* position, char digit, char board[9][9]){

  /* Check if a valid digit is entered. */
  if (digit > '9' || digit < '0')
  {
    cerr << endl << "(Error: This Sudoku puzzle only allows integers from 0 - 9.)" << endl;
    return false;
  }

  /*Check if a valid position is entered*/
  if (strlen(position) > 2)
  {
    cerr << endl << "(Error: This Sudoku puzzle is 2-D, please enter a two digit position.)" << endl;
    return false;
  }

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

  /*Check row, column and block for duplicates, if a valid move then place digit.*/
  if (all_checks(position, digit, board))
  {
     /*Place digit in position*/
    board[position[0]-'A'][position[1]-'1'] = digit;
    return true;
  }
  return false;
}

/*boolean check function to check if the digit already appears on the board at the row in position.
Returns false if the digit does appear in the row and true otherwise. */
bool row_check(const char* position, char digit, const char board[9][9])
{
  int row = position[0]-'A';
  for (int i = 0; i < 9; i++)
  {
    if (board[row][i] == digit)
      return false;
  }
  return true;
}

//Overload row-check to accept row as an integer
bool row_check(int row, char digit, const char board[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    if (board[row][i] == digit)
      return false;
  }
  return true;
}

/*Boolean check function to check if the digit appears on the board at the column in position.
Returns false if the digit does already appear in the column and true otherwise.*/

bool column_check(const char* position, char digit, const char board[9][9])
{
  int column = position[1]-'1';
  for (int i = 0; i < 9; i++)
  {
    if (board[i][column] == digit)
      return false;
  }
  return true;
}

//overload column check function to accept column number as an integer
bool column_check(int column, char digit, const char board[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    if (board[i][column] == digit)
      return false;
  }
  return true;
}

/*Boolean check function to check if digit already exists in the block that the position
  exists in. Returns false if the digit does appear in the block and true otherwise. */

bool block_check(const char* position, char digit, const char board[9][9])
{
  //declare block row number between 0-2 and block column number between 0-2.
  int block_row, block_column;

  block_row = (position[0] - 'A')/3;
  block_column = (position[1] - '1')/3;

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

//overload function to accept integers for row and column
bool block_check(int row, int column, char digit, const char board[9][9])
{
  //declare block row number between 0-2 and block column number between 0-2.
  int block_row, block_column;

  block_row = row/3;
  block_column = column/3;

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

//function to do row, column and block check in one. Returns true if all true and false otherwise.
bool all_checks(const char* position, char digit, const char board[9][9])
{
  if (row_check(position, digit, board) && column_check(position, digit, board) && block_check(position, digit, board))
    return true;
  return false;
}

//overload function all_checks to allow row and column to be entered as integers.
bool all_checks(int row, int column, char digit, const char board[9][9])
{
  //convert row and column into string constant position
  char position_temp[2];
  position_temp[0] = static_cast<char>(row + 'A');
  position_temp[1] = static_cast<char>(column + '1');
  const char* position = position_temp;

  if (all_checks(position, digit, board))
    return true;

  return false;
}

//Question 3 - function to save board in a text file called filename.

bool save_board(const char* filename, const char board[9][9])
{
  ofstream  out_stream;
  out_stream.open(filename);

  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      out_stream << board[i][j];
      //check for failure
      if (out_stream.fail())
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

/*Question4 - a boolean function that attempts to solve a sudoku puzzle in
input/output parameter board. Return value is true if a solution in found and
false otherwise. */

/*function solve_board:
Takes a 9 x 9 partially completed sudoku board.
If solving the board is possible then it returns true and the solved board.
If solving the board is not possible then it returns false. */
bool solve_board(char board[9][9])
{
  int row, column;
  char current_digit = '1', board_copy[9][9];
  bool error = false;

  make_board_copy(board, board_copy); //make a copy for this recursion
  error = !auto_fill(board_copy); //run all tools (autofill) and if error found report it

  if (is_complete(board_copy)) //check if board is complete
  {
    make_board_copy(board_copy, board); //if complete copy board to original board_copy
    return true;
  }
  else if (error)
  {
    return false;
  }
  else
  {
    find_first_empty_box(row, column, board_copy);
    do
    {
      if (current_digit == '9') //if got to digit 9 and not working
        return false;
      first_valid_digit(row, column, current_digit, board_copy);
      board_copy[row][column] = current_digit;
    } while(!solve_board(board_copy));
    make_board_copy(board_copy, board);
    return true;
  }
}

/*fills in suduko board using block duplicates theory. Only fills in boxes if digit
definitely belongs there. Returns 0 if no changes have been made (at a dead end), returns 1
if it has made changes and returns 2 if it has come across an error (no digit fits in a box)  */
int block_duplicates_tool(char board[9][9])
{
  int count, flag_x, flag_y, row, column, changes = 0;
  for (char k = '1'; k <= '9'; k++) //for each row block
  {
    for (int i = 0; i < 3; i++) //for each column block
    {
      for (int j = 0; j < 3; j++) //for each possible digit
      {
        if (block_check(3*i, 3*j, k, board)) //check for digit already in block
        {
          count = 0;
          for (int x = 0; x < 3; x++) //for each row in block
          {
            for (int y = 0; y < 3; y++) //for each column in block
            {
              row = (3*i)+x;
              column = (3*j)+y;
              if (board[row][column]=='.' && row_check(row, k, board) && column_check(column, k, board)) //check box is not already full and valid character
              {
                //cout << k << " can fit into row: " << row << "and column: " << column << endl;
                count++;
                flag_x = x;
                flag_y = y;
              }
            }
          }
          if (count == 1) //check for count = 1 meaning character must go in that space!
          {
            board[3 * i + flag_x][3 * j + flag_y] = k;
            changes = 1;
          }
          if (count == 0) //  if count == 0 then no possible moves are VALID in this box
            {
              return 5;
            }
        }
      }
    }
  }
  return changes;
}

int column_duplicates_tool(char board[9][9])
{
  int count, row_flag, changes = 0;
  for (char k = '1'; k <= '9'; k++) //for each character
  {
    for (int i = 0; i < 9; i++) //for each column
    {
      if (column_check(i, k, board)) //check if is digit already in column
      {
        count = 0;
        for (int j = 0; j < 9; j++) //for each row
        {
          if (board[j][i] == '.' && row_check(j, k, board) && block_check(j, i, k, board))
          {
            count++;
            row_flag = j;
          }
        }
        if (count == 1)
        {
          board[row_flag][i] = k;
          changes = 1;
        }
        if (count == 0)
        {
          return 5;
        }
      }
    }
  }
  return changes;
}

int row_duplicates_tool(char board[9][9])
{
  int count, column_flag, changes = 0;
  for (char k = '1'; k <= '9'; k++) //for each character
  {
    for (int i = 0; i < 9; i++) //for each row
    {
      if (row_check(i, k, board)) //check if digit is already in row
      {
        count = 0;
        for (int j = 0; j < 9; j++) //for each column
        {
          if (board[i][j] == '.' && column_check(j, k, board) && block_check(i, j, k, board))
          {
            count++;
            column_flag = j;
          }
        }
        if (count == 1)
        {
          board[i][column_flag] = k;
          changes = 1;
        }
        if (count == 0)
          return 5;
      }
    }
  }
  return changes;
}

/*Function that uses all tools in an interation until no more spaces can be filled with
100% certainty.
Returns false if a box is found with no valid digit.
Returns true when all changes have been made.*/
bool auto_fill(char board[9][9])
{
  int counter;
  while(!is_complete(board))
  {
    counter = (block_duplicates_tool(board) + column_duplicates_tool(board) + row_duplicates_tool(board));
    if(counter == 0) // Therefore no more changes are possible using tools
      return true;
    if(counter>=5) // Therefore an error has occured and board is not solvable
      return false;
  }
  return true; // In the case that the board is already solved
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
changes the argument current_digit to equal this*/
void first_valid_digit(int row, int column, char &current_digit, char board[9][9])
{
  for (; current_digit < '9'; current_digit++)
  {
    if (all_checks(row, column, current_digit, board))
    {
      return;
    }
  }
}

/*Function that creates a copy of board */
void make_board_copy(const char board[9][9], char board_copy[9][9])
{
  for (int i = 0; i < 9; i++) //for each row
  {
    for (int j = 0; j < 9; j++) //for each column
    {
      board_copy[i][j] = board[i][j];
    }
  }
}