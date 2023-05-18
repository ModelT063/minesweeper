#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

tile **initializeBoard(int difficulty)
{
	const int maxSize = 100;

	// Making maximum custom board 100x100
	// initialize 100x100 but only use up to difficulty
	tile **board = malloc(maxSize * sizeof(tile *));
	for (int i = 0; i < maxSize; i++)
	{
		board[i] = malloc(maxSize * sizeof(tile));

		for (int j = 0; j < maxSize; j++)
		{
			board[i][j].disp = '#';
			board[i][j].val = 0;
			board[i][j].vis = false;
		}
	}

	// initializes val of each tile
	initializeData(board, difficulty);
	return board;
}

void initializeData(tile **board, int difficulty)
{
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);

	int bomb = difficulty == 3 ? H_BOMB : (difficulty == 2 ? M_BOMB : E_BOMB);
	int fraction_bomb = (h * w) / bomb + 1;
	int bomb_num = 0;
	srand(time(0));

	// generates bombs
	while (bomb_num < bomb)
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				if (rand() % (h * w) < fraction_bomb && bomb_num < bomb)
				{
					board[i][j].val = -1;
					bomb_num++;
				}
			}
		}
	}

	// fills in proper numbers
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (board[i][j].val != -1)
			{
				// bottom left
				if (i != 0 && j != 0 && board[i - 1][j - 1].val == -1)
					board[i][j].val++;

				// left
				if (i != 0 && board[i - 1][j].val == -1)
					board[i][j].val++;

				// top left
				if (i != 0 && j != h - 1 && board[i - 1][j + 1].val == -1)
					board[i][j].val++;

				// top
				if (j != h - 1 && board[i][j + 1].val == -1)
					board[i][j].val++;

				// top right
				if (i != w - 1 && j != h - 1 && board[i + 1][j + 1].val == -1)
					board[i][j].val++;

				// right
				if (i != w - 1 && board[i + 1][j].val == -1)
					board[i][j].val++;

				// bottom right
				if (i != w - 1 && j != 0 && board[i + 1][j - 1].val == -1)
					board[i][j].val++;

				// bottom
				if (j != 0 && board[i][j - 1].val == -1)
					board[i][j].val++;
			}
		}
	}
}

bool updateGameBoard(tile **gameBoard, UsrIn *usr)
{
	// if space already selected, do nothing
	if (gameBoard[usr->w][usr->h].vis)
		return true;

	// flag action
	if (usr->choice == 'f')
	{
		if (gameBoard[usr->w][usr->h].disp == 'F')
			gameBoard[usr->w][usr->h].disp = '#';
		else
			gameBoard[usr->w][usr->h].disp = 'F';
	}
	// reveal tile action
	else if (usr->choice == 'r')
	{
		// if user selects a bomb space
		if (gameBoard[usr->w][usr->h].val == -1)
		{
			gameBoard[usr->w][usr->h].disp = 'B';
			gameBoard[usr->w][usr->h].vis = true;
			return false;
		}
		// if the tile isn't flagged, allow it to be revealed
		else if (gameBoard[usr->w][usr->h].disp != 'F')
		{
			gameBoard[usr->w][usr->h].disp = gameBoard[usr->w][usr->h].val + '0';
			gameBoard[usr->w][usr->h].vis = true;
		}
	}

	// Performs recursion to clear any 0s adjacent to user chosen 0
	if (usr->choice == 'r' && gameBoard[usr->w][usr->h].val == 0)
	{
		// defines a fake user input for recursion
		UsrIn temp = {'r', usr->d, 0, 0};
		int h = usr->d == 3 ? H_HEIGHT : (usr->d == 2 ? M_HEIGHT : E_HEIGHT);
		int w = usr->d == 3 ? H_WIDTH : (usr->d == 2 ? M_WIDTH : E_WIDTH);

		// bottom left
		if (usr->w != 0 && usr->h != 0)
		{
			temp.w = usr->w - 1;
			temp.h = usr->h - 1;
			updateGameBoard(gameBoard, &temp);
		}

		// left
		if (usr->w != 0)
		{
			temp.w = usr->w - 1;
			temp.h = usr->h;
			updateGameBoard(gameBoard, &temp);
		}

		// top left
		if (usr->w != 0 && usr->h != h - 1)
		{
			temp.w = usr->w - 1;
			temp.h = usr->h + 1;
			updateGameBoard(gameBoard, &temp);
		}

		// top
		if (usr->h != h - 1)
		{
			temp.w = usr->w;
			temp.h = usr->h + 1;
			updateGameBoard(gameBoard, &temp);
		}

		// top right
		if (usr->w != w - 1 && usr->h != h - 1)
		{
			temp.w = usr->w + 1;
			temp.h = usr->h + 1;
			updateGameBoard(gameBoard, &temp);
		}

		// right
		if (usr->w != w - 1)
		{
			temp.w = usr->w + 1;
			temp.h = usr->h;
			updateGameBoard(gameBoard, &temp);
		}

		// bottom right
		if (usr->w != w - 1 && usr->h != 0)
		{
			temp.w = usr->w + 1;
			temp.h = usr->h - 1;
			updateGameBoard(gameBoard, &temp);
		}

		// bottom
		if (usr->h != 0)
		{
			temp.w = usr->w;
			temp.h = usr->h - 1;
			updateGameBoard(gameBoard, &temp);
		}
	}
	return true;
}

bool gameWin(tile **gameBoard, int difficulty)
{
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);

	// goes through every tile, checks if it's visible
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			// if not visibile, return false unless it's a bomb
			if (!gameBoard[i][j].vis && gameBoard[i][j].val != -1)
				return false;
		}
	}
	return true;
}

void boardReveal(tile **gameBoard, int difficulty)
{
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (gameBoard[i][j].val == -1)
				gameBoard[i][j].disp = 'B';
			else
				gameBoard[i][j].disp = gameBoard[i][j].val + '0';
		}
	}
}

void gameReset(tile **gameBoard, UsrIn *usr)
{
	//  reprompts user for difficulty
	usr->d = difficultyMenu();

	if (usr->d == 5)
	{
		usr->choice = 'q';
		usr->d = 3;
	} // chose exit on menu
	if (usr->d == 4)
		usr->d = 3; // custom not implemented

	int h = usr->d == 3 ? H_HEIGHT : (usr->d == 2 ? M_HEIGHT : E_HEIGHT);
	int w = usr->d == 3 ? H_WIDTH : (usr->d == 2 ? M_WIDTH : E_WIDTH);

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			gameBoard[i][j].disp = '#';
			gameBoard[i][j].val = 0;
			gameBoard[i][j].vis = false;
		}
	}

	initializeData(gameBoard, usr->d);
}

void printBoard(tile **gameBoard, int difficulty)
{
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);

	// prints header of board
	printf("\n    |");
	for (int i = 0; i < w; i++)
		printf("%2d|", i);
	printf("\n    ");
	for (int j = 0; j < w; j++)
		printf("+--");
	puts("+");

	for (int i = 0; i < h; i++)
	{
		// prints board data
		printf("%4d", i);
		for (int j = 0; j < w; j++)
		{
			// prints everything in color
			switch (gameBoard[j][i].disp)
			{
			case '0':
				printf("|%2c", gameBoard[j][i].disp);
				break;
			case '1':
				printf("|\033[;31m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case '2':
				printf("|\033[;32m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case '3':
				printf("|\033[;33m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case '4':
				printf("|\033[;34m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case '5':
				printf("|\033[;35m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case '6':
				printf("|\033[;36m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case '7':
				printf("|\033[;37m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case '8':
				printf("|\033[;37m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case 'F':
				printf("|\033[37;41m%2c\033[0m", gameBoard[j][i].disp);
				break;
			case 'B':
				printf("|\033[30;41m%2c\033[0m", gameBoard[j][i].disp);
				break;
			default:
				printf("|\033[;47m%2c\033[0m", gameBoard[j][i].disp);
			}
		}
		printf("|\n    ");

		// prints horizontal dividers
		for (int j = 0; j < w; j++)
			printf("+--");
		puts("+");
	}
}

void printDiffMenu(WINDOW *window, int highlight, int nChoices, char **choices)
{
	int x = 2;
	int y = 4;
	box(window, 0, 0);

	char *str1 = "Use arrow keys to go up and down";
	char *str2 = "Press enter to select a difficulty";
	// use hardcoded length of strings to center them in the box
	mvwprintw(window, 1, window->_maxx / 2 - 32 / 2, str1);
	mvwprintw(window, 2, window->_maxx / 2 - 34 / 2, str2);

	for (int i = 0; i < nChoices; ++i)
	{
		if (highlight == i + 1) /* High light the present choice */
		{
			wattron(window, A_REVERSE);
			if (i == nChoices - 1)
				mvwprintw(window, y + 1, x, "%s", choices[i]); // prints exit 1 space away
			else
				mvwprintw(window, y, x, "%s", choices[i]);
			wattroff(window, A_REVERSE);
		}
		else if (i == nChoices - 1)
			mvwprintw(window, y + 1, x, "%s", choices[i]); // prints exit 1 space away
		else
			mvwprintw(window, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(window);
}

void printLogo(int col)
{
	int printX = col / 2 - 82 / 2; /*82 is length of logo*/
	mvprintw(1, printX, "   ________    ____   __  ____                                                   \n");
	mvprintw(2, printX, "  / ____/ /   /  _/  /  |/  (_)___  ___  ______      _____  ___  ____  ___  _____\n");
	mvprintw(3, printX, " / /   / /    / /   / /|_/ / / __ \\/ _ \\/ ___/ | /| / / _ \\/ _ \\/ __ \\/ _ \\/ ___/\n");
	mvprintw(4, printX, "/ /___/ /____/ /   / /  / / / / / /  __(__  )| |/ |/ /  __/  __/ /_/ /  __/ /    \n");
	mvprintw(5, printX, "\\____/_____/___/  /_/  /_/_/_/ /_/\\___/____/ |__/|__/\\___/\\___/ .___/\\___/_/  \n");
	mvprintw(6, printX, "                                                             /_/                 \n");
}

int difficultyMenu()
{
	char *choices[] = {
		"Easy",
		"Medium",
		"Hard",
		"Custom",
		"Exit"};
	int nChoices = 5;
	int row, col;
	int choice = 0;
	int c;
	int highlight = 1;

	// init window
	initscr();
	getmaxyx(stdscr, row, col);
	clear();
	noecho();
	cbreak();

	// define the window for the menu
	WINDOW *window = newwin(row / 2, 2 * col / 3, row / 4, col / 6);

	// enable directional keys
	keypad(window, TRUE);

	printLogo(col);
	refresh();
	printDiffMenu(window, highlight, nChoices, choices);
	while (1)
	{
		// gets user input
		c = wgetch(window);
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = nChoices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == nChoices)
				highlight = 1;
			else
				++highlight;
			break;
		case 10: // enter is pressed
			choice = highlight;
			break;
		default:
			// do nothing if other character is pressed
			break;
		}
		printDiffMenu(window, highlight, nChoices, choices);
		if (choice != 0) /* User did a choice come out of the infinite loop */
			break;
	}

	clrtoeol();
	refresh();
	endwin();
	return choice;
}

void clearWindow()
{
	// clears input buffer
	while (getchar() != '\n')
		;
	// clears the terminal
	printf("\e[1;1H\e[2J\e[3J");
}

void freeBoard(tile **board, int difficulty)
{
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	for (int i = 0; i < w; i++)
		free(board[i]);
	free(board);
	board = NULL;
}
