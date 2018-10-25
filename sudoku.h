#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool make_move(const char* position, char digit, char board[9][9]);
bool save_board(const char* filename, const char board[9][9]);
bool column_check(int column, char digit, const char board[9][9]);
bool row_check(int row, char digit, const char board[9][9]);
bool block_check(int row, int column, char digit, const char board[9][9]);
bool all_checks(int row, int column, char digit, const char board[9][9]);
bool solve_board(char board[9][9]);
void find_first_empty_box(int &row, int &column, const char board[9][9]);
bool find_next_valid_digit(int row, int column, char &current_digit, char board[9][9]);

#endif
