#define FRAMERATE 20
#define FIELD_SIDE 70
#include "console.h"
#include "atom.h"
#include "radioactivity.h"
#include <conio.h>

int *field[FIELD_SIDE][FIELD_SIDE];


void fieldDelete(int x, int y){
	int *currentCell = field[x][y];
	//for (int i = 0; i != 6; i++){
		//currentCell[i] = 0;
	//}
	currentCell[ATOMIC_NUMBER] = 0;
	currentCell[ATOMIC_WEIGHT] = 0;
	field[x][y] = NULL;
}


void fieldClear(){
	for (int x = 0; x != FIELD_SIDE; x++){
		for (int y = 0; y != FIELD_SIDE; y++){
			field[x][y] = NULL;
		}
	}
}


void setupScreen(){
	setWindowSize(FIELD_SIDE, FIELD_SIDE);

}
int *Particle(int atomicWeight, int atomicNumber, int color){
	int *particle = initializeParticle(atomicWeight, atomicNumber, color);
	field[particle[X_COORD]][particle[Y_COORD]] = particle;
	return particle;
}


int *Player(int atomicWeight, int atomicNumber, int color){
	//creates the player array
	int* player = Particle(atomicWeight, atomicNumber, color);
	player[X_COORD] = 1;
	player[Y_COORD] = 1;
	field[player[X_COORD]][player[Y_COORD]] = player;
	return player;
}

bool wallCollisionCheck(int *particle, bool side){
    if (side) return particle[X_COORD] <= 0  || particle[X_COORD] >= FIELD_SIDE - 1;
	else return particle[Y_COORD] <= 0 || particle[Y_COORD] >= FIELD_SIDE - 1;
}

void fieldMove(int *particle){
	//moves a  particle according to its velocity
	if (particle[ATOMIC_NUMBER] == 0 && particle[ATOMIC_WEIGHT] == 0){
		return;
	}


	else if (wallCollisionCheck(particle, true)){
        destroyLastParticleInstance(particle);
        particle[X_COORD] = abs(FIELD_SIDE - particle[X_COORD] - 3);
        fieldMove(particle);
		return;
	}
	else if (wallCollisionCheck(particle, false)){
        destroyLastParticleInstance(particle);
        particle[Y_COORD] = abs(FIELD_SIDE - particle[Y_COORD] - 3);
        fieldMove(particle);
        return;
	}


    else{
        int previousX = particle[X_COORD];
        int previousY = particle[Y_COORD];
        runParticle(particle);
        //cout << particle[X_COORD];
        //field[previousX][previousY] = NULL;
        field[particle[X_COORD]][particle[Y_COORD]] = particle;
    }
}

void setFrameDelay(){
	Sleep((int) 1000 / FRAMERATE);

}

void controls(int &velocityX, int &velocityY){
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
}

bool isParticle(int x, int y){
    char currentChar = getConsoleChar(x, y);
    return currentChar == NEUTRON || currentChar == PROTON; //add other particles later
}

int* getCollidedObjectFoundIn(int x, int y){
	if (isParticle(x - 1, y)){
		return getCollidedObjectFoundIn(x - 1, y);
	}
	else if (isParticle(x, y - 1)){
		return getCollidedObjectFoundIn(x, y - 1);
	}
	else{
		return field[x][y];
	}
}


int* advancedCollisionCheck(int *particle){
	int x = particle[X_COORD];
	int y = particle[Y_COORD];

	int dimension = getDimension(particle);
	int velocityX = particle[X_VELOCITY];
	int velocityY = particle[Y_VELOCITY];
	//Four sided collision detection
	for (int i = 0; i != dimension; i++){
		if (velocityX > 0){
			if (isParticle(x + dimension, y + i)){
				return getCollidedObjectFoundIn(x + dimension, y + i);
			}
		}
		/*
		else if (velocityX < 0){
			if (getConsoleChar(x - velocityX, y + i) != ' '){
				return getCollidedObjectFoundIn(x - velocityX, y + i);
			}
		}*/

		else if (velocityY > 0){
			if (getConsoleChar(x + i, y + dimension) != ' '){
				return getCollidedObjectFoundIn(x + i, y + dimension);
			}
		}
		/*
		else if (velocityY < 0){
			if (getConsoleChar(x + i, y - velocityY) != ' '){
				return getCollidedObjectFoundIn(x + i, y - velocityY);
			}
		}*/
	}
	//gotoxy(0,0);
	//cout << "FUCK";
	return NULL;

}


void addAtomTo(int *atoms[], int pos, int color){
	int *newParticle = Particle(4,2,color); //randomize later
	newParticle[X_COORD] = rand() % FIELD_SIDE;
	newParticle[Y_COORD] = rand() % FIELD_SIDE;
	//int i = 0;
//	while (atoms[i] != NULL) i++;
	atoms[pos] = newParticle;
}

void groupFieldMove(int *atoms[], int size){
	int i = 0;
	while(i <= size){
		fieldMove(atoms[i]);
		i++;
	}
}



void groupUpdateVelocity(int *enemies[], int size){
	int i = 0;
	while (i <= size){
        velocity(enemies[i], rand() % 3 - 1, rand() % 3 - 1);
		i++;
	}
}


int framesPerSpawn = 30;

int groupDecayParticles(int *enemies[], int spawnCount){
    int counter = 0;
    for (int i = 0; i != spawnCount; i++){
        if (enemies[i]){
            int *emission = decayParticle(enemies[i]);
            if (emission){
                frame += framesPerSpawn;
                addAtomTo(enemies, ++spawnCount, enemies[i][COLOR]);
                counter++;
                }
        }
    }
    return counter;
}

void enemyHandler(int *enemies[], int size, int frameNumber){
    int spawnCount = (int)floor(frameNumber / framesPerSpawn);
	if (frameNumber % framesPerSpawn == 0) addAtomTo(enemies, spawnCount, TWHITE);
	spawnCount += groupDecayParticles(enemies, spawnCount);
	groupUpdateVelocity(enemies, spawnCount);
	groupFieldMove(enemies, spawnCount);
}

