#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
	UsrIn usr = {'y', 0, 0, 0};
	bool lose = false;
	// prints welcome message and difficulty selector	
	printf("Welcome to Command Line Minesweeper!\n");
	do{
		printf("Choose your difficulty:\n\tEasy - 1\n\tMedium - 2\n\tHard - 3\n\nEnter: ");
		scanf("%d", &usr.d);
		clear();
	} while(usr.d <= 0 || usr.d >= 4);
	
	// creates gameboard
	tile** gameBoard = initializeBoard(usr.d);
	
	while(usr.choice != 'q'){
		printBoard(gameBoard, usr.d);
		
		printf("\nAction: ");
		usr.choice = getchar();
		printf("Column: ");
		scanf("%d", &usr.w);
		printf("Row: ");
		scanf("%d", &usr.h);
		clear();

		// Write function to validate usr input
	
		lose = !updateGameBoard(gameBoard, &usr);
		
		// runs win/lose messages
		if(gameWin(gameBoard, usr.d) || lose){
			if(!lose)
				printf("\nYOU WON! :D");
			else
				printf("\nYou Lose :(");
		
			// prompts user to play again	
			while(usr.choice != 'y' && usr.choice != 'n'){
				// reveals and prints the finished board
				boardReveal(gameBoard, usr.d);
				printBoard(gameBoard, usr.d);
				
				printf("\nWould you like to play again?\n\nEnter 'y' or 'n': ");
				usr.choice = getchar();
				clear();
			}
		
			if(usr.choice == 'n'){
				usr.choice = 'q';
				freeBoard(gameBoard, usr.d);
			}
			else{ 
				gameReset(gameBoard, &usr);}
		}
	}

	return 0;
}
