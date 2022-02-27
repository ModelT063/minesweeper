#ifndef functions_h
#define functions_h

char** initializeBoard(int difficulty);
int** initializeData(int difficulty);
void printBoard(char** gameBoard, int difficulty);
void freeBoard(void** board, int difficulty);

#endif
