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
//char representation of each particle
const char NEUTRON = 'o';
const char PROTON = '+';
const char ELECTRON = '-';
const char POSITRON = '%';

//prototypes
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
	Positron: number = 1, weight = 0
	*/
	//initializes the particles and sets all its properties to 0 except for the atomic weight, atomic and color
	//int atomicWeight: atomic weight of the particle
	//int atomicNumber: atomic number of the particle
    //int color: color of the particle
	int* particle = (int*) malloc(7 * sizeof(int)); //7 PROPERTIES as described by the variables above
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
    //prints elemParticle at x,y with color color
    //x, y: coords
    //int elemParticle: char of the particle
    //int color: number code of the color
    textcolor(color);
    //if the cursor is not already at x,y, go to x,y.
    //this reduces the necessary number of calls to putxy, which is a slower function than using printf in a straight line
    if (whereX() != x || whereY() != y)
        gotoxy(x, y);
    printf("%c", elemParticle);
}


//a set of functions that print out the different types of particles
//int x: x-coord
//int y: y-coord
//int color: color of the particle
void placePositronIn(int x, int y, int color){
    efficientPrinter(x, y, POSITRON, color);
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
    //activates the flashing collision effect
    //int repeats: number of flashes
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
    //int* particle: particle to be moved
    //int xMovement: movement in the x-direction
    //int yMovement: movement in the y-direction
	destroyLastParticleInstance(particle); //destroys the last instance before printing a new one
	particle[X_COORD] += xMovement;
	particle[Y_COORD] += yMovement;
	int* collidedObject = advancedCollisionCheck(particle);
	if (collidedObject && collidedObject != particle){
		//creates collision effect if player collides with another atom
		if (collidedObject == player || particle == player)
            collisionEffect(5);
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
    //moves int* particle according to its velocities per frame
	moveParticle(particle, particle[X_VELOCITY], particle[Y_VELOCITY]);
}

void velocity(int *particle, int x_velocity, int y_velocity){
    //updates the particle's velocities
    //int x_velocity: new x-velocity
    //int y_velocity: new y-velocity
	particle[X_VELOCITY] = x_velocity;
	particle[Y_VELOCITY] = y_velocity;
}

int getDimension(int *particle){
    //gets the dimension of the particle needed to fit it into a square
	return (int) floor(sqrt(particle[ATOMIC_WEIGHT])) + 1;
}


