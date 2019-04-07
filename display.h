void paintAtom(int color);

void placeParticle(int* particle){
	//places the particle in its current stored distance
	int color = particle[COLOR];
	int dimension = getDimension(particle);
	/*int charge = particle[ATOMIC_NUMBER];
	int neutrons = particle[ATOMIC_WEIGHT] - charge;
	int x = particle[X_COORD];
	int y_reset = particle[Y_COORD];
	int y = particle[Y_COORD];
	while (charge != 0 && neutrons != 0){
		if (charge > 0){
			placeProtonIn(x, y);
			charge--;
		}
		else if (charge < 0){
			charge++;
			y++;
		}

	}*/

	int placedNeutrons = 0;
	int placedProtons = 0;
	bool outOfProtons = false;
	bool outOfNeutrons = false;
	int atom = 0;
	for (int curY = particle[Y_COORD]; curY != particle[Y_COORD] + dimension; curY++){
		for (int curX = particle[X_COORD]; curX != particle[X_COORD] + dimension; curX++){
			outOfProtons = placedProtons == particle[ATOMIC_NUMBER];
			outOfNeutrons = placedNeutrons == particle[ATOMIC_WEIGHT] - particle[ATOMIC_NUMBER];

			if (((curX - particle[X_COORD] % 2 != curY - particle[Y_COORD] % 2)  || outOfProtons) && !outOfNeutrons){
				placeNeutronIn(curX, curY, color);
				placedNeutrons++;
			}
			else if (!outOfProtons){
				placeProtonIn(curX, curY, color);
				placedProtons++;
			}


			atom++;


		}
	}

}

void destroyLastParticleInstance(int* particle){
	//places the particle in its current stored distance
	int dimension = getDimension(particle);
	for (int curY = particle[Y_COORD]; curY < particle[Y_COORD] + dimension; curY++){
		for (int curX = particle[X_COORD]; curX < particle[X_COORD] + dimension; curX++){
			putxy(curX, curY, TBLACK, "  ");
		}
	}
}

