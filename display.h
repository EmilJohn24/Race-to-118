void paintAtom(int color);

void placeParticle(int* particle){
	//places the particle in its current stored distance
	//int* particle: a pointer to an array containing the particle to be placed
    if (particle[ATOMIC_NUMBER] == -1){
        placeElectronIn(particle[X_COORD],particle[Y_COORD],particle[COLOR]);
        return;
    }

    if (particle[ATOMIC_NUMBER] == 1 && particle[ATOMIC_WEIGHT] == 0){
        placePositronIn(particle[X_COORD],particle[Y_COORD],particle[COLOR]);
        return;
    }
	int color = particle[COLOR];
	int dimension = getDimension(particle);
	int placedNeutrons = 0;
	int placedProtons = 0;
	bool outOfProtons = false;
	bool outOfNeutrons = false;
	int newX, newY;
	int atom = 0;
	for (int curY = particle[Y_COORD]; curY != (particle[Y_COORD] + dimension); curY++){
		for (int curX = particle[X_COORD]; curX != (particle[X_COORD] + dimension); curX++){
		    newX = curX % FIELD_SIDE;
            newY = curY % FIELD_SIDE;
			outOfProtons = placedProtons == particle[ATOMIC_NUMBER];
			outOfNeutrons = placedNeutrons == particle[ATOMIC_WEIGHT] - particle[ATOMIC_NUMBER];

			if (((curX - particle[X_COORD] % 2 != curY - particle[Y_COORD] % 2)  || outOfProtons) && !outOfNeutrons){
				placeNeutronIn(newX, newY, color);
				placedNeutrons++;
			}
			else if (!outOfProtons){
				placeProtonIn(newX, newY, color);
				placedProtons++;
			}


			atom++;


		}
	}

}

void gameOverSequence(){
    //displays the game over screen
    int row = 0;
    int col = 0;
    while (row < FIELD_SIDE * 2 || col < FIELD_SIDE * 2){
        getConsoleWindowSize(&row, &col);
        setWindowSize(FIELD_SIDE * 2, FIELD_SIDE * 2);
        setScreenSize(FIELD_SIDE * 2, FIELD_SIDE * 2);
    }
    //prints game over
    gotoxy(0,0);
    printf("..######......###....##.....##.########.....#######..##.....##.########.########.\n.##....##....##.##...###...###.##..........##.....##.##.....##.##.......##.....##\n.##.........##...##..####.####.##..........##.....##.##.....##.##.......##.....##\n.##...####.##.....##.##.###.##.######......##.....##.##.....##.######...########.\n.##....##..#########.##.....##.##..........##.....##..##...##..##.......##...##..\n.##....##..##.....##.##.....##.##..........##.....##...##.##...##.......##....##.\n..######...##.....##.##.....##.########.....#######.....###....########.##.....##");
    Sleep(10000);
    exit(0);
}

void destroyLastParticleInstance(int* particle){
    //destroys the last instance of a particle displayed on screen
    //int* particle: particle to be destroyed
    textcolor(TBLACK);
    int newX, newY;
	//places the particle in its current stored distance
	int dimension = getDimension(particle);
	for (int curY = particle[Y_COORD]; curY <= particle[Y_COORD] + dimension; curY++){
		for (int curX = particle[X_COORD]; curX <= particle[X_COORD] + dimension; curX++){
            newX = curX % FIELD_SIDE;
            newY = curY % FIELD_SIDE;
            if (whereX() != curX || whereY() != curY)
                gotoxy(newX, newY);
            printf(" ");
		}
	}
}

void displayPlayerData(int* player){
    //displays the data of an atom (used mainly for the player)
    //int* player: a pointer to an array containing the player's data
    gotoxy(0,0);
    float playerAtomicRatio = (float)player[ATOMIC_NUMBER] / (float)(player[ATOMIC_WEIGHT] - player[ATOMIC_NUMBER]);
    printf("Atomic Number: %d\n", player[ATOMIC_NUMBER]);
    printf("Atomic Weight: %d\n", player[ATOMIC_WEIGHT]);
    printf("Atomic Ratio: %.2f\n", playerAtomicRatio);
    printf("Player Coords: %d,%d\n", player[X_COORD], player[Y_COORD]);
    printf("Player Velocity: %2d %2d\n", player[X_VELOCITY], player[Y_VELOCITY]);


}

