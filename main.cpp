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
//LATEST
/*
Some design considerations (A Prelude):




*/
int main(){
    welcomePage();
	setupScreen();
	srand(time(0));
    player = Player(40, 20, TBLUE); //array containing the player object
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
		/*
		if (emission && frame % DECAY_INTERVAL == 1){
            int spawnCount = (int)floor(frame / framesPerSpawn);
            addAtomTo(otherAtoms, spawnCount + 1, TBLUE);
            int* newAtom = otherAtoms[spawnCount + 1];
            newAtom[X_COORD] = player[X_COORD] + getDimension(player) + 2;
            newAtom[Y_COORD] = player[Y_COORD];
            newAtom[ATOMIC_WEIGHT] = emission[ATOMIC_WEIGHT];
            newAtom[ATOMIC_NUMBER] = emission[ATOMIC_NUMBER];
            newAtom[X_VELOCITY] = -velocityX;
            newAtom[Y_VELOCITY] = -velocityY;
            newAtom[COLOR] = emission[COLOR];
            frame += framesPerSpawn;
		}*/

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

