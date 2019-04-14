// Magic Numbers: 2,8,20,28,50,82,126
#define DECAY_INTERVAL 31
int* Particle(int atomicWeight, int atomicNumber, int color);

int* alphaDecay(int *particle){
    particle[ATOMIC_NUMBER] -= 2;
    particle[ATOMIC_WEIGHT] -= 4;
    return Particle(4, 2, TWHITE);
}

int* betaDecay(int *particle){
    particle[ATOMIC_NUMBER]++;
    return Particle(0,-1,TRED);
}

int* positronDecay(int *particle){
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

const float standardError = 0.05;
const float alphaError = 0.15;
int* decayParticle(int* particle){
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

