#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main(void){
	struct UsrIn usr = {'0', 0, 0, 0};
	
	// prints welcome message and difficulty selector	
	printf("Welcome to Command Line Minesweeper!\n");
	do{
		printf("Choose your difficulty:\n\tEasy - 1\n\tMedium - 2\n\tHard - 3\n\nEnter: ");
		scanf("%d", &usr.d);
		clear();
	} while(usr.d <= 0 || usr.d >= 4);
	
	// creates gameboard
	char** gameBoard = initializeBoard(usr.d);
	int** boardData = initializeData(usr.d);
	
	while(usr.choice != 'q'){
		printBoard(gameBoard, usr.d);
		
		printf("\nAction: ");
		usr.choice = getchar();
		// -48 to correct ascii value to int
		usr.x = getchar() - 48;
		usr.y = getchar() - 48;
		clear();
	}

	freeBoard((void**)gameBoard, usr.d);
	freeBoard((void**)boardData, usr.d);
	return 0;
}
