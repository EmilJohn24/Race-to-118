//#define FRAMERATE 20
int FRAMERATE = 20;
#define FIELD_SIDE 75
#include "console.h"
#include "atom.h"
#include "radioactivity.h"
#include <conio.h>

int *field[FIELD_SIDE][FIELD_SIDE];


void fieldDelete(int x, int y){
    //deletes the particle at coord x, y in the field
    //int x: x-coord of the particle to be destroyed
    //int y: y-coord of the particle to be destroyed
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
    //int atomicWeight: thr atomic weight of the particle
    //int atomicNumber: the atomic number of the particle
    //int color: the color of the particle
	int *particle = initializeParticle(atomicWeight, atomicNumber, color);
	field[particle[X_COORD]][particle[Y_COORD]] = particle;
	return particle;
}


int *Player(int atomicWeight, int atomicNumber, int color){
	//creates the player array
	//uses the Particle function to create the player object but overrides the x and y-coordinates
	int* player = Particle(atomicWeight, atomicNumber, color);
	player[X_COORD] = FIELD_SIDE / 2;
	player[Y_COORD] = FIELD_SIDE / 2;
	field[player[X_COORD]][player[Y_COORD]] = player;
	return player;
}

bool wallCollisionCheck(int *particle, bool side){
    //checks if an atom has collided on the walls of the field
    //int *particle: the particle to be checked for
    //bool side: true if the check applies to the left or right side, false otherwise
    if (side) return particle[X_COORD] <= 0  || particle[X_COORD] >= FIELD_SIDE - 1;
	else return particle[Y_COORD] <= 0 || particle[Y_COORD] >= FIELD_SIDE - 1;
}

void fieldMove(int *particle){
	//moves a  particle according to its velocity
	//int *particle: particle to be moved
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
    //FRAMERATE: number of refreshes per second
	Sleep((int) 1000 / FRAMERATE);

}

void controls(int &velocityX, int &velocityY){
    //gets a key from the keyboard and changes the velocities appropriately
    //int &velocityX: x-velocity
    //int &velocityY: y-velocity
    /*
        khbit is a built-in member function of conio.h that checks the key press buffer
    */
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
    //int x: x-coord
    //int y: y-coord
    //returns true if there is a particle at x,y
    char currentChar = getConsoleChar(x, y);
    return currentChar == NEUTRON || currentChar == PROTON || currentChar == ELECTRON || currentChar == POSITRON; //add other particles later
}

int* getCollidedObjectFoundIn(int x, int y){
    //uses recursion to find the actual field coordinate of a particle at x,y
    //tracks the nearest neighboring particle to recursively find the stored coord of the particle
    //this is necessary because only the top-left coord of the particle is actually stored
    //returns a pointer to the tracked object
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
    //returns a pointer to the object that you collided with otherwise
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
    //int *particle: the particle to be checked
    //returns true if the particle is dead
    return particle[ATOMIC_WEIGHT] == 0 && particle[ATOMIC_NUMBER] == 0;

}

void addAtomTo(int *atoms[], int pos, int color){
    //adds an atom to an atom group (array)
    //int *atoms[]: an array containing pointers to the atoms in memory
    //int pos: the position of the new atom in the array
    //int color: the color of the new atom
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

void randomWalk(int *particle){
    if (rand() % 2 == 0)
        velocity(particle, rand() % 3 - 1, 0);
    else
        velocity(particle, 0, rand() % 3 - 1);


}

void playerAttractor(int *particle){
    //attracts the particle to the player
    int playerX = player[X_COORD];
    int playerY = player[Y_COORD];
    if (playerX - particle[X_COORD] > 0) velocity(particle, 1, 0);
    else if (playerX - particle[X_COORD] < 0) velocity(particle, -1, 0);
    else if (playerY - particle[Y_COORD] > 0) velocity(particle, 0, 1);
    else if (playerY - particle[Y_COORD] < 0) velocity(particle, 0, -1);

}

void groupUpdateVelocity(int *enemies[], int size){
    //updates the velocity of the enemies
    //presently uses a random walk algorithm
    //int *enemies[]: an array of pointers to the enemies
    //int size: size of the enemies
	int i = 0;
	while (i <= size){
        //the particles take a random walk 3/4 of the time and goes to the player for the remaining 1/4
        if (rand() % 4 != 0){
            randomWalk(enemies[i]);
        }
        else{
            //player attraction
            playerAttractor(enemies[i]);

        }
        i++;
	}

}


int framesPerSpawn = 40; //number of frames before a new enemy is spawned
int groupDecayParticles(int *enemies[], int spawnCount){
    //decays an array of atoms
    //int *enemies[]: group of enemies
    //int spawnCount: number of enemies spawned at the time of the call
    //returns the number of newly-decayed particles
    int counter = 0;
    for (int i = 0; i != spawnCount; i++){
        if (enemies[i]){
            int *emission = decayParticle(enemies[i]);
            if (emitter(emission, enemies[i], frame, framesPerSpawn, enemies))
                counter++;
            }
        }
    return counter;
}

void enemyHandler(int *enemies[], int size, int frameNumber){
    //handles all enemy actions
    //all parameters same as the ones discussed on top
    int spawnCount = (int)floor(frameNumber / framesPerSpawn);
	if (frameNumber % framesPerSpawn == 0) addAtomTo(enemies, spawnCount, TWHITE);
	spawnCount += groupDecayParticles(enemies, spawnCount);
	groupUpdateVelocity(enemies, spawnCount);
	groupFieldMove(enemies, spawnCount);
}

