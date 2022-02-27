#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

const int E_BOMB = 10;
const int E_HEIGHT = 10;
const int E_WIDTH = 10;
const int M_BOMB = 15;
const int M_HEIGHT = 15;
const int M_WIDTH = 20;
const int H_BOMB = 25;
const int H_HEIGHT = 50;
const int H_WIDTH = 100;

char** initializeBoard(int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	int bomb = difficulty == 3 ? H_BOMB : (difficulty == 2 ? M_BOMB : E_BOMB);
	
	char** board = (char**)malloc(sizeof(char*) * w);
	for(int i = 0; i < w; i++){
		board[i] = (char*)malloc(sizeof(char) * h);
		
		for(int j = 0; j < h; j++)
			board[i][j] = '.';	
	}
	return board;
}

int** initializeData(int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	int bomb = difficulty == 3 ? H_BOMB : (difficulty == 2 ? M_BOMB : E_BOMB);
	int bomb_num = 0;

	// initializes data to 0
	int** board = (int**)malloc(sizeof(int*) * w);
	for(int i = 0; i < w; i++){
		board[i] = (int*)malloc(sizeof(int) * h);
		
		for(int j = 0; j < h; j++)
			board[i][j] = 0;	
	}
	
	// generates bombs
	for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
			if(rand() % 100 < 10 && bomb_num < bomb){
				board[i][j] = -1;
				bomb_num++;
			}
		}
	}	
	
	// fills in proper numbers
	for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
			if(board[i][j] != -1){
				// bottom left
				if(i != 0 && j != 0){
					if(board[i - 1][j - 1] == -1)
						board[i][j]++;
				}
				// left
				if(i != 0){
					if(board[i - 1][j] == -1)
						board[i][j]++;
				}
				// top left
				if(i != 0 && j != h - 1){
					if(board[i - 1][j] == -1)
						board[i][j]++;
				}
				// top
				if(j != h - 1){
					if(board[i][j + 1] == -1)
						board[i][j]++;
				}
				// top right
				if(i != w - 1 && j != h - 1){
					if(board[i + 1][j + 1] == -1)
						board[i][j]++;
				}
				// right
				if(i != w - 1){
					if(board[i + 1][j] == -1)
						board[i][j]++;
				}
				// bottom right
				if(i != w - 1 && j != 0){
					if(board[i + 1][j - 1] == -1)
						board[i][j]++;
				}
				// bottom
				if(j != 0){
					if(board[i][j - 1] == -1)
						board[i][j]++;
				}
			}
		}
	}
							
	return board;
}

// maybe make this return a string instead of print everything at some point?
void printBoard(char** gameBoard, int difficulty){
	int h = difficulty == 3 ? H_HEIGHT : (difficulty == 2 ? M_HEIGHT : E_HEIGHT);
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);

	for(int i = 0; i < (w * 2) + 1; i++) printf("-");
	printf("\n");

	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++)
			printf("|%c", gameBoard[j][i]);
		puts("|");
	}

	for(int i = 0; i < (w * 2) + 1; i++) printf("-");
	printf("\n");
}

void freeBoard(void** board, int difficulty){
	int w = difficulty == 3 ? H_WIDTH : (difficulty == 2 ? M_WIDTH : E_WIDTH);
	for(int i = 0; i < w; i++) free(board[i]);
	free(board);
}

