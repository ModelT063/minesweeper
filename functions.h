#ifndef functions_h
#define functions_h

#include <stdbool.h>

#define E_BOMB 10
#define E_HEIGHT 9
#define E_WIDTH 9

#define M_BOMB 40
#define M_HEIGHT 16
#define M_WIDTH 16

#define H_BOMB 99
#define H_HEIGHT 16
#define H_WIDTH 30

typedef struct
{
	// a single char representing any current user input
	char choice;
	// the difficulty of the current game
	int d;
	// user selection of a tile
	int w;
	int h;
} UsrIn;

// a single square on the minesweeper board
typedef struct
{
	// the display character, visible to user
	// could either be a blank square or a flag
	char disp;

	// the true value of the tile, regardless of display
	// -1 = bomb
	// <num> = number of bombs surrounding (0-8)
	int val;

	// true if the true value is displayed to user
	bool vis;
} tile;

// allocates memory for the game based on the size the user chose
tile **initializeBoard(int difficulty);

// initializes the allocated data, adding bombs and number values
void initializeData(tile **board, int difficulty);

// changes the visibility of a tile or flags one, returns false if updates visibility of a bomb, true otherwise
bool updateGameBoard(tile **board, UsrIn *usr);

// checks to see if the game has been won
bool gameWin(tile **gameBoard, int difficulty);

// displays all values on the board at the end of the game
void boardReveal(tile **gameBoard, int difficulty);

// resets neccessary info for a new game to start
void gameReset(tile **gameBoard, UsrIn *usr);

// prints the board to the terminal
void printBoard(tile **board, int difficulty);

// prints difficulty menu to the terminal
int printMenu();

// clears input buffer and terminal screen
void clear(void);

// frees the memory allocated by the game board
void freeBoard(tile **board, int difficulty);

#endif
