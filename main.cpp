#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int frame = 0;
int *player;
#include "game.h"
#include "display.h"
#include "welcome.h"
#define ENEMY_SIZE 100000

/*
Some design considerations (A Prelude):




*/
int main(){
    welcomePage();
	setupScreen();
	srand(time(0));
    player = Player(4, 2, TBLUE);
	int *otherAtoms[ENEMY_SIZE];
	int velocityX = 0;
	int velocityY = 0;
	fieldClear();
    //game proper
	while (true){
		setFrameDelay();
		displayPlayerData(player);
		controls(velocityX, velocityY);
        velocity(player, velocityX, velocityY);
		decayParticle(player);
		fieldMove(player);
		enemyHandler(otherAtoms, ENEMY_SIZE, frame);
		frame++;
		if (isDefeated(player)) gameOverSequence();
	}
}

