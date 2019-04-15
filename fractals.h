/* A tiny fractal library built on top of console.h*/
/*
    After coming across a fractals video on Youtube, I became intrugied by
    how they are implemented computationally.
*/
void fernDisplay(float initialX, float initialY, int fernPixels, float scaling){
    //procedurally generates a ferna
    srand(time(0)); //setting up the seed based on the current time
    float x[fernPixels] = {initialX};
    float y[fernPixels] = {initialX};
    int percent;
    for (int pixel = 1; pixel != fernPixels; pixel++){
        percent = rand() % 100;
        if (percent < 1){
            x[pixel] = 0;
            y[pixel] = 0.16 * y[pixel - 1];
        }

        else if (percent < 86){
            x[pixel] = 0.85 * x[pixel - 1] + 0.04 * y[pixel - 1];
            y[pixel] = -0.04 * x[pixel - 1] + 0.85 * y[pixel - 1] + 1.6;
        }

        else if (percent < 93){
            x[pixel] = 0.2 * x[pixel - 1] - 0.26 * y[pixel - 1];
            y[pixel] = 0.23 * x[pixel - 1] + 0.22 * y[pixel - 1] + 1.6;
        }

        else{
            x[pixel] = -0.15 * x[pixel - 1] + 0.28 * y[pixel - 1];
            y[pixel] = 0.26 * x[pixel - 1] + 0.24 * y[pixel - 1] + 0.44;
        }
    }

    for (int pixel = 1; pixel != fernPixels; pixel++){
        putxy(x[pixel] * scaling + initialX, y[pixel] * scaling + initialY, TGREEN, "*");
    }

}

void sierpinskisTriangle(float vertexA[2], float vertexB[2], float vertexC[2], int pixels, int color){
    const int X = 0, Y = 1;
    srand(time(0));
    float vertex[2] = {(float)(rand() % WELCOME_SCREEN_SIZE), (float)(rand() % WELCOME_SCREEN_SIZE)};
    int position = rand() % 3;
    putxy(vertexA[X], vertexA[Y], TRED, "o");\
    putxy(vertexB[X], vertexB[Y], TBLUE, "o");
    putxy(vertexC[X], vertexC[Y], TGREEN, "o");
    for (int pixel = 0; pixel != pixels; pixel++){
        position = rand() % 3;
        switch(position){
        case 0:
            vertex[X] = (vertexA[X] + vertex[X]) / 2;
            vertex[Y] = (vertexA[Y] + vertex[Y]) / 2;
            break;
        case 1:
            vertex[X] = (vertexB[X] + vertex[X]) / 2;
            vertex[Y] = (vertexB[Y] + vertex[Y]) / 2;
            break;
        case 2:
            vertex[X] = (vertexC[X] + vertex[X]) / 2;
            vertex[Y] = (vertexC[Y] + vertex[Y]) / 2;
            break;
        }
        putxy(vertex[X], vertex[Y], color, "*");
    }

}
