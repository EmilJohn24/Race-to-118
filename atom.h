//atom[3][NUM_OF_NUCLIDES]
//The three inner elements would represent:
//1. Type: (Neutron = 0, Proton = 1, None = 2)
//2. X-coodinate
//3. Y-coordinate
#include <stdlib.h>
#include <math.h>
#define MAX_ATOMIC_WEIGHT 294
//Indexes for the properties of the atom
int ATOMIC_WEIGHT = 0;
int ATOMIC_NUMBER = 1;
int X_COORD = 2;
int Y_COORD = 3;
int X_VELOCITY = 4;
int Y_VELOCITY = 5;
int COLOR = 6;
const char NEUTRON = 'o';
const char PROTON = '+';
const char ELECTRON = '-';
//const char POSITRON = 'O';
void destroyLastParticleInstance(int* particle);
void placeParticle(int* particle);
int* advancedCollisionCheck(int *particle);
void fieldDelete(int x, int y);
int* getField();
void displayPlayerData(int* player);

int* initializeParticle(int atomicWeight, int atomicNumber, int color){
	/*Quick Guide:
	Neutron: number = 0, weight = 1
	Proton: number = 1, weight = 1
	Electron: number = -1, weight = 0
	Alpha: number = 2, weight = 4
	*/
	//initializes the particles and sets all its properties to 0 except for the atomic weight, atomic and color
	int* particle = (int*) malloc(7 * sizeof(int)); //7 PROPERTIES
	particle[ATOMIC_WEIGHT] = atomicWeight;
	particle[ATOMIC_NUMBER] = atomicNumber;
	particle[X_COORD] = 0;
	particle[Y_COORD] = 0;
	particle[X_VELOCITY] = 0;
	particle[Y_VELOCITY] = 0;
	particle[COLOR] = color;
	return particle;
}
void efficientPrinter(int x, int y, int elemParticle, int color){
    textcolor(color);
    if (whereX() != x || whereY() != y)
        gotoxy(x, y);
    printf("%c", elemParticle);
}

void placeElectronIn(int x, int y, int color){
    efficientPrinter(x, y, ELECTRON, color);
}


void placeNeutronIn(int x, int y, int color){
    efficientPrinter(x, y, NEUTRON, color);
}

void placeProtonIn(int x, int y, int color){
    efficientPrinter(x, y, PROTON, color);
}

void collisionEffect(int repeats){
	for (int repeat = 0; repeat != repeats; repeat++){
		setBackgroundColor(BWHITE);
		Sleep(100);
		setBackgroundColor(BBLACK);
	}
}

void paintAtom(int color){
	textcolor(color);
}

void moveParticle(int* particle, int xMovement, int yMovement){
	destroyLastParticleInstance(particle);
	particle[X_COORD] += xMovement;
	particle[Y_COORD] += yMovement;
	int* collidedObject = advancedCollisionCheck(particle);
	if (collidedObject){
		//creates collision effect if player collides with another atom
		if (collidedObject == player || particle == player) collisionEffect(5);
		particle[ATOMIC_WEIGHT] += collidedObject[ATOMIC_WEIGHT];
		particle[ATOMIC_NUMBER] += collidedObject[ATOMIC_NUMBER];
		destroyLastParticleInstance(collidedObject);
		collidedObject[X_VELOCITY] = 0;
		collidedObject[Y_VELOCITY] = 0;
		collidedObject[ATOMIC_NUMBER] = 0;
		collidedObject[ATOMIC_WEIGHT] = 0;
	}
	placeParticle(particle);
}

void runParticle(int *particle){
	moveParticle(particle, particle[X_VELOCITY], particle[Y_VELOCITY]);
}

void velocity(int *particle, int x_velocity, int y_velocity){
	particle[X_VELOCITY] = x_velocity;
	particle[Y_VELOCITY] = y_velocity;
}

int getDimension(int *particle){
	return (int) floor(sqrt(particle[ATOMIC_WEIGHT])) + 1;
}


