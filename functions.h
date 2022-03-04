#ifndef functions_h
#define functions_h

#include <stdbool.h>

typedef struct {
	char choice;
	int d;
	int w;
	int h;
} UsrIn;

typedef struct {
	char disp;
	int val;
	bool vis;
} tile;

// allocates memory for the game based on the size the user chose
tile** initializeBoard(int difficulty);

// initializes the allocated data, adding bombs and number values
void initializeData(tile** board, int difficulty);

// changes the visibility of a tile or flags one, returns false if updates visibility of a bomb, true otherwise
bool updateGameBoard(tile** board, UsrIn *usr);

// checks to see if the game has been won
bool gameWin(tile** gameBoard, int difficulty);

// resets neccessary info for a new game to start
void gameReset(tile** gameBoard, UsrIn *usr);

// prints the board to the terminal
void printBoard(tile** board, int difficulty);

// clears input buffer and terminal screen
void clear(void);

// frees the memory allocated by the game board
void freeBoard(tile** board, int difficulty);

#endif
