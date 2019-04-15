// Magic Numbers: 2,8,20,28,50,82,126
#define DECAY_INTERVAL 31
int* Particle(int atomicWeight, int atomicNumber, int color);
void addAtomTo(int* atoms[], int pos, int color);

/*
	A Quick Guide on the types of nuclear decay:
		https://www.toppr.com/guides/physics/nuclei/radioactivity-types-of-radioactive-decay/

*/
int* alphaDecay(int *particle){
	//executes alpha decay on a particle and returns the new alpha particle
    particle[ATOMIC_NUMBER] -= 2;
    particle[ATOMIC_WEIGHT] -= 4;
    return Particle(4, 2, TWHITE);
}

int* betaDecay(int *particle){
	//executes beta decay on a particle and returns the new beta particle
	//Note: A Beta Particle is just an electron
    particle[ATOMIC_NUMBER]++;
    return Particle(0,-1,TRED);
}

int* positronDecay(int *particle){
	//executes positron decay on a particle and returns the new positron
    particle[ATOMIC_NUMBER]--;
    return Particle(0,1,TYELLOW);
}

bool exceptions(int* particle){
    if (particle[ATOMIC_NUMBER] == 1) return true;
    if (particle[ATOMIC_NUMBER] == 2 && particle[ATOMIC_WEIGHT] == 5){
        return true;
    }

    return false;
}

/*
This was the primary guide for the particle decay logic:
https://chem.libretexts.org/Bookshelves/Physical_and_Theoretical_Chemistry_Textbook_Maps/Supplemental_Modules_(Physical_and_Theoretical_Chemistry)/Nuclear_Chemistry/Nuclear_Energetics_and_Stability/Nuclear_Magic_Numbers
*/
const float standardError = 0.05;
const float alphaError = 0.15;
int* decayParticle(int* particle){
	//checks if the particle is to decay and returns the emitted particle if yes
    int protons = particle[ATOMIC_NUMBER];
    int neutrons = particle[ATOMIC_WEIGHT] - protons;
    float atomicRatio = (float)neutrons / (float)protons;
    gotoxy(0,1);
    if (protons <= 0) return NULL;
    if (protons <= 20 && !exceptions(particle)){
        if (atomicRatio > 1)
            return betaDecay(particle);
        else if (atomicRatio < 1)
            return positronDecay(particle);
        else
            return NULL;
    }

    if (protons > 20 && protons < 84 && !exceptions(particle)){
        if (atomicRatio > 1.5 + standardError)
            return betaDecay(particle);
        else if (atomicRatio < 1.5 - standardError)
            return positronDecay(particle);
        else
            return NULL;

    }

    if (protons > 84){
        if (fabs(atomicRatio - 1.5) > alphaError)
            return alphaDecay(particle);
        //place alpha decay stuff here
    }
    return NULL;

}


bool emitter(int *emission, int *emittee, int &frame, int &framesPerSpawn, int *outputGroup[]){
    if (emission && frame % DECAY_INTERVAL == 1){
        int spawnCount = (int)floor(frame / framesPerSpawn);
        addAtomTo(outputGroup, spawnCount + 1, TBLUE);
        int* newAtom = outputGroup[spawnCount + 1];
        newAtom[X_COORD] = emittee[X_COORD] + getDimension(player) + 2;
        newAtom[Y_COORD] = emittee[Y_COORD];
        newAtom[ATOMIC_WEIGHT] = emission[ATOMIC_WEIGHT];
        newAtom[ATOMIC_NUMBER] = emission[ATOMIC_NUMBER];
        newAtom[X_VELOCITY] = -emittee[X_VELOCITY];
        newAtom[Y_VELOCITY] = -emittee[Y_VELOCITY];
        newAtom[COLOR] = emission[COLOR];
        frame += framesPerSpawn;
        return true;
    }
    return false;


}
