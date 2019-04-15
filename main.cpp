#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int frame = 0; //counts the number of frames passed
int *player; //stores the player object
bool stable = true;
#include "game.h"
#include "display.h"
#include "welcome.h"
#define ENEMY_SIZE 100000

int main(){
    welcomePage();
	setupScreen();
	srand(time(0));
    player = Player(4, 2, TBLUE); //array containing the player object
	int *otherAtoms[ENEMY_SIZE]; //array of pointers to enemy atoms
	int velocityX = 0; //player velocity in x-dir
	int velocityY = 0; //player velocity in y-dir
	fieldClear();
    //game proper
	while (true){
		setFrameDelay();
		displayPlayerData(player);
		controls(velocityX, velocityY);
        velocity(player, velocityX, velocityY);
		int* emission = decayParticle(player); //pointer to emitted decayed particle from player
		stable = !emission;
		emitter(emission, player, frame, framesPerSpawn, otherAtoms);
		fieldMove(player);
		enemyHandler(otherAtoms, ENEMY_SIZE, frame);
		frame++;
		if (isDefeated(player)){
                gameOverSequence();
                break;
		}
		if (player[ATOMIC_NUMBER] >= 118){
                victorySequence();
                break;
		}
	}
	main();
}

