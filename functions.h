#ifndef functions_h
#define functions_h

typedef struct UsrIn{
	char choice;
	int d;
	int x;
	int y;
} usr;

char** initializeBoard(int difficulty);
int** initializeData(int difficulty);
void updateGameBoard(struct UsrIn usr, int difficulty);
void printBoard(char** gameBoard, int difficulty);
void clear(void);
void freeBoard(void** board, int difficulty);

#endif
