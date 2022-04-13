#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

const int E_BOMB = 10,
		  E_HEIGHT = 9,
		  E_WIDTH = 9,
		  
		  M_BOMB = 40,
		  M_HEIGHT = 16,
		  M_WIDTH = 16,
		  
		  H_BOMB = 99,
		  H_HEIGHT = 16,
		  H_WIDTH = 30;

tile** initializeBoard(int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	int bomb = difficulty == 3 ? H_BOMB : (difficulty == 2 ? M_BOMB : E_BOMB);
	
	tile** board = malloc(w * sizeof(tile*));
	for(int i = 0; i < w; i++){
		board[i] = malloc(h * sizeof(tile));
		
		for(int j = 0; j < h; j++){
			board[i][j].disp = '#';
			board[i][j].val = 0;
			board[i][j].vis = false;
		}	
	}
	
	// initializes val of each tile
	initializeData(board, difficulty);
	return board;
}

void initializeData(tile** board, int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	
	int bomb = difficulty == 3 ? H_BOMB : (difficulty == 2 ? M_BOMB : E_BOMB);
	int fraction_bomb = (h * w) / bomb + 1;
	int bomb_num = 0;
	srand(time(0));

	// generates bombs
	while(bomb_num < bomb){
		for(int i = 0; i < w; i++){
			for(int j = 0; j < h; j++){
				if(rand() % (h * w) < fraction_bomb && bomb_num < bomb){
					board[i][j].val = -1;
					bomb_num++;
				}
			}
		}	
	}

	// fills in proper numbers
	for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
			if(board[i][j].val != -1){
				// bottom left
				if(i != 0 && j != 0 && board[i - 1][j - 1].val == -1)
					board[i][j].val++;
			
				// left
				if(i != 0 && board[i - 1][j].val == -1)
					board[i][j].val++;
				
				// top left
				if(i != 0 && j != h - 1 && board[i - 1][j + 1].val == -1)
					board[i][j].val++;
				
				// top
				if(j != h - 1 && board[i][j + 1].val == -1)
					board[i][j].val++;
				
				// top right
				if(i != w - 1 && j != h - 1 && board[i + 1][j + 1].val == -1)
					board[i][j].val++;
				
				// right
				if(i != w - 1 && board[i + 1][j].val == -1)
					board[i][j].val++;
				
				// bottom right
				if(i != w - 1 && j != 0 && board[i + 1][j - 1].val == -1)
					board[i][j].val++;
				
				// bottom
				if(j != 0 && board[i][j - 1].val == -1)
					board[i][j].val++;
			}
		}
	}
}

bool updateGameBoard(tile** gameBoard, UsrIn *usr){
	// if space already selected, do nothing
	if(gameBoard[usr->w][usr->h].vis) return true;

	// flag action 
	if(usr->choice == 'f'){
		if(gameBoard[usr->w][usr->h].disp == 'F')
			gameBoard[usr->w][usr->h].disp = '#';
		else
			gameBoard[usr->w][usr->h].disp = 'F';
	}
	// reveal tile action
	else if(usr->choice == 'r'){
		// if user selects a bomb space
		if(gameBoard[usr->w][usr->h].val == -1){
			gameBoard[usr->w][usr->h].disp = 'B';
			gameBoard[usr->w][usr->h].vis = true;	
			return false;
		}
		// if the tile isn't flagged, allow it to be revealed
		else if(gameBoard[usr->w][usr->h].disp != 'F'){
			gameBoard[usr->w][usr->h].disp = gameBoard[usr->w][usr->h].val + '0'; 
			gameBoard[usr->w][usr->h].vis = true;	
		}
	}

	// Performs recursion to clear any 0s adjacent to user chosen 0 									
	if(usr->choice == 'r' && gameBoard[usr->w][usr->h].val == 0){
		// defines a fake user input for recursion
		UsrIn temp = {'r', usr->d, 0, 0};
		int h = usr->d == 3 ? H_HEIGHT : (usr->d == 2 ? M_HEIGHT : E_HEIGHT);
		int w = usr->d == 3 ? H_WIDTH : (usr->d == 2 ? M_WIDTH : E_WIDTH);
			
		// bottom left
		if(usr->w != 0 && usr->h != 0){
			temp.w = usr->w - 1;
			temp.h = usr->h - 1;
			updateGameBoard(gameBoard, &temp);
		}	
		
		// left
		if(usr->w != 0){
	   		temp.w = usr->w - 1;
			temp.h = usr->h;
			updateGameBoard(gameBoard, &temp);
		}			
		
		// top left
		if(usr->w != 0 && usr->h != h - 1){
			temp.w = usr->w - 1;
			temp.h = usr->h + 1;
			updateGameBoard(gameBoard, &temp);
		}			

		// top
		if(usr->h != h - 1){
			temp.w = usr->w;
			temp.h = usr->h + 1;
			updateGameBoard(gameBoard, &temp);
		}

		// top right
		if(usr->w != w - 1 && usr->h != h - 1){
			temp.w = usr->w + 1;
			temp.h = usr->h + 1;
			updateGameBoard(gameBoard, &temp);
		}
				
		// right
		if(usr->w != w - 1){
			temp.w = usr->w + 1;
			temp.h = usr->h;
			updateGameBoard(gameBoard, &temp);
		}
				
		// bottom right
		if(usr->w != w - 1 && usr->h != 0){
			temp.w = usr->w + 1;
			temp.h = usr->h - 1;
			updateGameBoard(gameBoard, &temp);
		}		
		
		// bottom
		if(usr->h != 0){
			temp.w = usr->w;
			temp.h = usr->h - 1;
			updateGameBoard(gameBoard, &temp);
		}
	}
	return true;
}

bool gameWin(tile** gameBoard, int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);

	// goes through every tile, checks if it's visible
	for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
			// if not visibile, return false unless it's a bomb
			if(!gameBoard[i][j].vis && gameBoard[i][j].val != -1) 
				return false;
		}
	}
	return true;
}

void boardReveal(tile** gameBoard, int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	
	for(int i = 0; i < w; i++){	
		for(int j = 0; j < h; j++){
			if(gameBoard[i][j].val == -1)
				gameBoard[i][j].disp = 'B'; 
			else
				gameBoard[i][j].disp = gameBoard[i][j].val + '0'; 
		}
	}
}

void gameReset(tile** gameBoard, UsrIn *usr){
	//freeBoard(gameBoard, usr->d);
	// reprompts user for difficulty
	do{
		printf("Choose your difficulty:\n\tEasy - 1\n\tMedium - 2\n\tHard - 3\n\nEnter: ");
		scanf("%d", &usr->d);
		clear();
	} while(usr->d <= 0 || usr->d >= 4);
	
	int h = usr->d == 3 ? H_HEIGHT : (usr->d == 2 ? M_HEIGHT : E_HEIGHT);
	int w = usr->d == 3 ? H_WIDTH : (usr->d == 2 ? M_WIDTH : E_WIDTH);
	// reallocates based on new board size
	gameBoard = realloc(gameBoard, sizeof(tile*) * w);
	for(int i = 0; i < w; i++){
		gameBoard[i] = realloc(gameBoard[i], sizeof(tile) * h);
	
		for(int j = 0; j < h; j++){
			gameBoard[i][j].disp = '#';
			gameBoard[i][j].val = 0;
			gameBoard[i][j].vis = false;
		}	
	}
	
	initializeData(gameBoard, usr->d);
}

void printBoard(tile** gameBoard, int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);

	// prints header of board
	printf("\n    |");
	for(int i = 0; i < w; i++) printf("%2d|", i);
	printf("\n    ");
	for(int j = 0; j < w; j++) printf("+--");
	puts("+");

	for(int i = 0; i < h; i++){
		// prints board data
		printf("%4d", i);
		for(int j = 0; j < w; j++){
			// prints everything in color
			switch(gameBoard[j][i].disp){
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
		for(int j = 0; j < w; j++) printf("+--");
		puts("+");
	}
}

void clear(void){
	// clears input buffer
	while(getchar() != '\n');
	// clears the terminal 
	printf("\e[1;1H\e[2J\e[3J");
}
	
void freeBoard(tile** board, int difficulty){
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	for(int i = 0; i < w; i++) free(board[i]);
	free(board);
	board = NULL;
}

