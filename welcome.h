#define WELCOME_SCREEN_SIZE 500
#include "fractals.h"

void changeFrameRate(){
    printf("New Frame Rate: ");
    scanf("%d", &FRAMERATE);
}

void welcomePage(){
    gotoxy(0,0);
    srand(time(0));
    printf("$$$$$$$\\                                        $$\\                       $$\\     $$\\    $$$$$$\\  \n$$  __$$\\                                       $$ |                    $$$$ |  $$$$ |  $$  __$$\\\n$$ |  $$ | $$$$$$\\   $$$$$$$\\  $$$$$$\\        $$$$$$\\    $$$$$$\\        \\_$$ |  \\_$$ |  $$ /  $$ |\n$$$$$$$  | \\____$$\\ $$  _____|$$  __$$\\       \\_$$  _|  $$  __$$\\         $$ |    $$ |   $$$$$$  |\n$$  __$$<  $$$$$$$ |$$ /      $$$$$$$$ |        $$ |    $$ /  $$ |        $$ |    $$ |  $$  __$$<\n$$ |  $$ |$$  __$$ |$$ |      $$   ____|        $$ |$$\\ $$ |  $$ |        $$ |    $$ |  $$ /  $$ |\n$$ |  $$ |\\$$$$$$$ |\\$$$$$$$\\ \\$$$$$$$\\         \\$$$$  |\\$$$$$$  |      $$$$$$\\ $$$$$$\\ \\$$$$$$  |\n\\__|  \\__| \\_______| \\_______| \\_______|         \\____/  \\______/       \\______|\\______| \\______/");
    printf("\n\n\nLoading...");
    printf("\n");
    setScreenSize(WELCOME_SCREEN_SIZE, WELCOME_SCREEN_SIZE);

    int loadingDisplay = rand() % 2;
    switch(loadingDisplay){
    case 0:
        fernDisplay(100, 10,120000, 25);
        break;
    case 1:
        float vertexA[2] = {25,15}, vertexB[2] = {0,80}, vertexC[2] = {60,60};
        float vertexD[2] = {80, 50};
        sierpinskisTriangle(vertexA, vertexB, vertexC, 100000, TYELLOW);
        sierpinskisTriangle(vertexA, vertexC, vertexD, 10000, TRED);
        break;
    }
    gotoxy(0,10);
    printf("Main Menu: \n");
    printf("1. Play Game\n");
    printf("2. Change Frame Rate \n");
    printf("3. Exit Game \n");

    char choice = getch(); //Windows only
    system("cls");
    switch(choice){
        case '1':
            return;
            break;
        case '2':
            changeFrameRate();
            break;
        case '3':
            exit(0);
            break;
    }
    system("cls");
    welcomePage();
}



/*
void tutorial(){
    int screenX = FIELD_SIDE;
    int screenY = FIELD_SIDE;
    int velocityX = 0, velocityY = 0;
    int center = FIELD_SIDE / 2;
    int *tutorialPlayer = Player(4,2,TBLUE);
    printf("Welcome to the tutorial...\n");
    printf("To begin, pay attention to the blue atom in the middle of the playing field...\n");
    printf("That's you...\n");

}
*/
