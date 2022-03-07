#ifndef functions_h
#define functions_h

#include <stdbool.h>

typedef struct {
	// a single char representing any current user input
	char choice;
	// the difficulty of the current game
	int d;
	// user selection of a tile
	int w;
	int h;
} UsrIn;

// a single square on the minesweeper board
typedef struct {
	// the display character, visible to user
	char disp;
	// the true value of the tile, regardless of display
	int val;
	// true if the true value is displayed to user
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

// displays all values on the board at the end of the game
void boardReveal(tile** gameBoard, int difficulty);

// resets neccessary info for a new game to start
void gameReset(tile** gameBoard, UsrIn *usr);

// prints the board to the terminal
void printBoard(tile** board, int difficulty);

// clears input buffer and terminal screen
void clear(void);

// frees the memory allocated by the game board
void freeBoard(tile** board, int difficulty);

#endif
