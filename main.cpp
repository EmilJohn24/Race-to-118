#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int frame = 0;
int *player;
#include "game.h"
#include "display.h"
#include "welcome.h"

#define ENEMY_SIZE 100000
int main(){
    welcomePage();
	setupScreen();
	srand(time(0));
    player = Player(4, 2, TBLUE);
	//int *player = Player(4, 2, TBLUE);
	int *otherAtoms[ENEMY_SIZE];
	int velocityX = 0;
	int velocityY = 0;
	fieldClear();
    float playerAtomicRatio;
	while (true){
		//printf("%d ", counter);
		//printf("%d ", enemy[X_COORD]);
		// cout << "1 ";
		setFrameDelay();
        playerAtomicRatio = (float)player[ATOMIC_NUMBER] / (float)(player[ATOMIC_WEIGHT] - player[ATOMIC_NUMBER]);
		// cout << "2 ";
		controls(velocityX, velocityY);
		// cout << "3 ";
        gotoxy(0,0);
        printf("Atomic Number: %d\n", player[ATOMIC_NUMBER]);
        printf("Atomic Weight: %d\n", player[ATOMIC_WEIGHT]);
        printf("Atomic Ratio: %.2f", playerAtomicRatio);
		velocity(player, velocityX, velocityY);
		decayParticle(player);
		// cout << "4 ";
		fieldMove(player);
        gotoxy(0,0);
		//cout << player[X_COORD];
		// cout << "5 ";
		enemyHandler(otherAtoms, ENEMY_SIZE, frame);
		// cout << "6 ";
		frame++;
		//gotoxy(50,50);
		//printf("%d", otherAtoms[0]);

	}
}

