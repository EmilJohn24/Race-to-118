#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int frame = 0;
int *player;
#include "game.h"
#include "display.h"
#include "welcome.h"
#define ENEMY_SIZE 120000

/*
Some design considerations (A Prelude):




*/
int main(){
    //welcomePage();
	setupScreen();
	srand(time(0));
    player = Player(40, 20, TBLUE);
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
		int* emission = decayParticle(player);

		if (emission && frame % DECAY_INTERVAL == 0){
            int spawnCount = (int)floor(frame / framesPerSpawn);
            addAtomTo(otherAtoms, spawnCount + 1, TBLUE);
            int* newAtom = otherAtoms[spawnCount + 1];
            newAtom[ATOMIC_WEIGHT] = emission[ATOMIC_WEIGHT];
            newAtom[ATOMIC_NUMBER] = emission[ATOMIC_NUMBER];
            newAtom[COLOR] = emission[COLOR];
            frame += framesPerSpawn;
		}

		fieldMove(player);
		enemyHandler(otherAtoms, ENEMY_SIZE, frame);
		frame++;
		if (isDefeated(player)) gameOverSequence();
	}
}

