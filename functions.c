#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const int E_BOMB = 10;
const int E_HEIGHT = 10;
const int E_WIDTH = 10;
const int M_BOMB = 15;
const int M_HEIGHT = 15;
const int M_WIDTH = 20;
const int H_BOMB = 25;
const int H_HEIGHT = 15;
const int H_WIDTH = 50;

tile** initializeBoard(int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	int bomb = difficulty == 3 ? H_BOMB : (difficulty == 2 ? M_BOMB : E_BOMB);
	
	tile** board = (tile**)malloc(sizeof(tile*) * w);
	for(int i = 0; i < w; i++){
		board[i] = (tile*)malloc(sizeof(tile) * h);
		
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
	int bomb_num = 0;
	
	// generates bombs																!!!!!!!!!!!!!!!REWORK BOMB MAKING ALGORITHM!!!!!!!!!!!!!
	for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
			if(rand() % 100 < 10 && bomb_num < bomb){
				board[i][j].val = -1;
				bomb_num++;
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
	if(usr->choice == 'f')
		gameBoard[usr->w][usr->h].disp = 'F';
	else{
		// if user selects a bomb space
		if(gameBoard[usr->w][usr->h].val == -1){
			gameBoard[usr->w][usr->h].disp = 'B';
			gameBoard[usr->w][usr->h].vis = true;	
			return false;
		}
		else{
			// user selects a normal tile
			gameBoard[usr->w][usr->h].disp = gameBoard[usr->w][usr->h].val + '0'; 
			gameBoard[usr->w][usr->h].vis = true;	
		}
	}
																//!!!!!!!!! write recursion for blank squares using similar method to data init !!!
	return true;
}

bool gameWin(tile** gameBoard, int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);

	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(!gameBoard[i][j].vis && gameBoard[i][j].val != -1) 
				return false;
		}
	}
	return true;
}

void gameReset(tile** gameBoard, UsrIn *usr){
	freeBoard(gameBoard, usr->d);

	do{
		printf("Choose your difficulty:\n\tEasy - 1\n\tMedium - 2\n\tHard - 3\n\nEnter: ");
		scanf("%d", &usr->d);
		clear();
	} while(usr->d <= 0 || usr->d >= 4);
	
	gameBoard = initializeBoard(usr->d);
}

// maybe make this return a string instead of print everything at some point?
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
	printf("\e[1;1H\e[2J");
}
	
void freeBoard(tile** board, int difficulty){
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	for(int i = 0; i < w; i++) free(board[i]);
	free(board);
}

