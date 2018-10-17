void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool make_move(char position[2], char digit, char board[9][9]);
bool save_board(char filename[], const char board[9][9]);
bool column_check(const char position[2], char digit, const char board[9][9]);
bool row_check(const char position[2], char digit, const char board[9][9]);
bool block_check(const char position[2], char digit, const char board[9][9]);
