#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main(void){
	
	// prints welcome message and difficulty selector	
	printf("Welcome to Command Line Minesweeper!\n");
	int diff;
	do{
		printf("Choose your difficulty:\n\tEasy - 1\n\tMedium - 2\n\tHard - 3\n\nEnter: ");
		scanf("%d", &diff);
	} while(diff <= 0 || diff >= 4);
	
	// creates gameboard
	char** gameBoard = initializeBoard(diff);
	int** boardData = initializeData(diff);
	
	printBoard(gameBoard, diff);

	freeBoard((void**)gameBoard, diff);
	freeBoard((void**)boardData, diff);
	return 0;
}
