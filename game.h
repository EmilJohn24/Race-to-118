#define FRAMERATE 20
#define FIELD_SIDE 50
#include "console.h"
#include "atom.h"
#include "radioactivity.h"
#include <conio.h>

int *field[FIELD_SIDE][FIELD_SIDE];


void fieldDelete(int x, int y){
    //deletes the particle at coord x, y in the field
	int *currentCell = field[x][y];
	currentCell[ATOMIC_NUMBER] = 0;
	currentCell[ATOMIC_WEIGHT] = 0;
	field[x][y] = NULL;
}


void fieldClear(){
    //empties the entire field
    //used for initiaization
	for (int x = 0; x != FIELD_SIDE; x++){
		for (int y = 0; y != FIELD_SIDE; y++){
			field[x][y] = NULL;
		}
	}
}


void setupScreen(){
    //sets up the screen size according to the FIELD_SIDE constant
	setWindowSize(FIELD_SIDE, FIELD_SIDE);

}
int *Particle(int atomicWeight, int atomicNumber, int color){
    //initializes a particle and puts it on the field
	int *particle = initializeParticle(atomicWeight, atomicNumber, color);
	field[particle[X_COORD]][particle[Y_COORD]] = particle;
	return particle;
}


int *Player(int atomicWeight, int atomicNumber, int color){
	//creates the player array
	int* player = Particle(atomicWeight, atomicNumber, color);
	player[X_COORD] = FIELD_SIDE / 2;
	player[Y_COORD] = FIELD_SIDE / 2;
	field[player[X_COORD]][player[Y_COORD]] = player;
	return player;
}

bool wallCollisionCheck(int *particle, bool side){
    //checks if an atom has collided on the walls of the field
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
        particle[X_COORD] =  abs(FIELD_SIDE - particle[X_COORD] - 3);
        fieldMove(particle);
		return;
	}
	else if (wallCollisionCheck(particle, false)){
        destroyLastParticleInstance(particle);
        particle[Y_COORD] = abs(FIELD_SIDE - particle[Y_COORD] - 2);
        fieldMove(particle);
        return;
	}


    else{
        runParticle(particle);
        field[particle[X_COORD]][particle[Y_COORD]] = particle;
    }
}

void setFrameDelay(){
    //frame control based on a customizable value for frame rate
	Sleep((int) 1000 / FRAMERATE);

}

void controls(int &velocityX, int &velocityY){
    //gets a key from the keyboard and changes the velocities appropriately
	if (kbhit()){
			char move = getch();
			switch(move){
			    //it is important to note that this is actually a case-sensitive selection process, and as such, there is a need for the capital cases
				case 'w': case 'W':
					velocityX = 0; velocityY = -1;
					break;
				case 'a': case 'A':
					velocityX = -1; velocityY = 0;
					break;
				case 's': case 'S':
					velocityX = 0; velocityY = 1;
					break;
				case 'd': case 'D':
					velocityX = 1; velocityY = 0;
					break;
				default:
					break;
			}


		}
}

bool isParticle(int x, int y){
    //checks if the object at x, y is a particle
    char currentChar = getConsoleChar(x, y);
    return currentChar == NEUTRON || currentChar == PROTON || currentChar == ELECTRON || currentChar == POSITRON; //add other particles later
}

int* getCollidedObjectFoundIn(int x, int y){
    //uses recursion to find the actual field coordinate of a particle at x,y
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
    //checks if a particle has collided with something and returns a pointer to the collided object
    //returns NULL if no collisions happened
	int x = particle[X_COORD];
	int y = particle[Y_COORD];

	int dimension = getDimension(particle) + 1;
	int velocityX = particle[X_VELOCITY];
	int velocityY = particle[Y_VELOCITY];
	//Four sided collision detection
	for (int i = 0; i != dimension; i++){
		if (velocityX > 0){
            textcolor(BYELLOW);
			if (isParticle(x + dimension, y + i)){
				return getCollidedObjectFoundIn(x + dimension, y + i);
			}
		}


		else if (velocityY > 0){
			if (isParticle(x + i, y + dimension)){
				return getCollidedObjectFoundIn(x + i, y + dimension);
			}
		}

	}

	return NULL;

}

bool isDefeated(int *particle){
    //checks if a particle has been defeated, i.e. it no longer has a weight
    return particle[ATOMIC_WEIGHT] == 0;

}

void addAtomTo(int *atoms[], int pos, int color){
    //adds an atom to an atom group (array)
	int *newParticle = Particle(4,2,color); //randomize later
	newParticle[X_COORD] = rand() % FIELD_SIDE;
	newParticle[Y_COORD] = rand() % FIELD_SIDE;
	atoms[pos] = newParticle;
}

void groupFieldMove(int *atoms[], int size){
    //moves a group of atoms according to their individually-stored velocities
	int i = 0;
	while(i <= size){
		fieldMove(atoms[i]);
		i++;
	}
}



void groupUpdateVelocity(int *enemies[], int size){
    //updates the velocity of the enemies
    //presently uses a random walk algorithm
	int i = 0;
	while (i <= size){
        if (rand() % 2 == 0)
            velocity(enemies[i], rand() % 3 - 1, 0);
        else
            velocity(enemies[i], 0, rand() % 3 - 1);
		i++;
	}
}


int framesPerSpawn = 40;
int groupDecayParticles(int *enemies[], int spawnCount){
    //decays an array of atoms
    int counter = 0;
    for (int i = 0; i != spawnCount; i++){
        if (enemies[i]){
            int *emission = decayParticle(enemies[i]);
            if (emission && frame % DECAY_INTERVAL == 0){
                frame += framesPerSpawn;
                addAtomTo(enemies, ++spawnCount, TWHITE);
                enemies[++spawnCount][ATOMIC_WEIGHT] = emission[ATOMIC_WEIGHT];
                enemies[spawnCount][ATOMIC_NUMBER] = emission[ATOMIC_NUMBER];
                enemies[spawnCount][COLOR] = emission[COLOR];
                counter++;
                }
        }
    }
    return counter;
}

void enemyHandler(int *enemies[], int size, int frameNumber){
    //handles all enemy actions
    int spawnCount = (int)floor(frameNumber / framesPerSpawn);
	if (frameNumber % framesPerSpawn == 0) addAtomTo(enemies, spawnCount, TWHITE);
	spawnCount += groupDecayParticles(enemies, spawnCount);
	groupUpdateVelocity(enemies, spawnCount);
	groupFieldMove(enemies, spawnCount);
}

