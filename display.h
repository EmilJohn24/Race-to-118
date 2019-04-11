void paintAtom(int color);

void placeParticle(int* particle){
	//places the particle in its current stored distance
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
    gotoxy(0,0);
    setWindowSize(FIELD_SIDE, FIELD_SIDE * 2);
    printf("..######......###....##.....##.########.....#######..##.....##.########.########.\n.##....##....##.##...###...###.##..........##.....##.##.....##.##.......##.....##\n.##.........##...##..####.####.##..........##.....##.##.....##.##.......##.....##\n.##...####.##.....##.##.###.##.######......##.....##.##.....##.######...########.\n.##....##..#########.##.....##.##..........##.....##..##...##..##.......##...##..\n.##....##..##.....##.##.....##.##..........##.....##...##.##...##.......##....##.\n..######...##.....##.##.....##.########.....#######.....###....########.##.....##");
    exit(0);
}

void destroyLastParticleInstance(int* particle){
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
    gotoxy(0,0);
    float playerAtomicRatio = (float)player[ATOMIC_NUMBER] / (float)(player[ATOMIC_WEIGHT] - player[ATOMIC_NUMBER]);
    printf("Atomic Number: %d\n", player[ATOMIC_NUMBER]);
    printf("Atomic Weight: %d\n", player[ATOMIC_WEIGHT]);
    printf("Atomic Ratio: %.2f\n", playerAtomicRatio);
    printf("Player Coords: %d,%d\n", player[X_COORD], player[Y_COORD]);
    printf("Player Velocity: %2d %2d\n", player[X_VELOCITY], player[Y_VELOCITY]);


}

