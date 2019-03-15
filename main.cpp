#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include <conio.h>
int main(){
	int *player = Player(4, 2);
	int velocityX = 0;
	int velocityY = 0;
	while (true){
		if (kbhit()){
			char move = getch();
			switch(move){
				case 'w':
					velocityX = 0; velocityY = -1;
					break;
				case 'a':
					velocityX = -1; velocityY = 0;
					break;
				case 's':
					velocityX = 0; velocityY = 1;
					break;
				case 'd':
					velocityX = 1; velocityY = 0;
					break;
				default:
					break;
			}


		}
		
		velocity(player, velocityX, velocityY);
		fieldMove(player);		
	}
}
