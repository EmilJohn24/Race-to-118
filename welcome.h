#define WELCOME_SCREEN_SIZE 500
#include "fractals.h"

void changeFrameRate(){
    printf("New Frame Rate: ");
    scanf("%d", &FRAMERATE);
}




void instructions(){
    system("cls");
    gotoxy(0,0);
    printf("--------Welcome to Race To 118--------- \n");
    printf("You are a lone helium atom that found yourself in a small void filled with different atoms. \n");
    printf("Your dream is to become Oganesson, the legendary element number 118 and the only way you can do so is to collide with other atoms \n");
    printf("Rules: \n");
    textcolor(TYELLOW);
    printf("\t1. Use the WASD keys to control your atom. (W = Left, A = Up, S = Down, D = Right)\n");
    printf("\t2. You can consume an atom by colliding with him to his left or above him. This is because of the strong gravitational pull in those directions.\n");
    printf("\t3. You will be consumed by any atom that hits your left or top part. Keep this in mind. Getting hit in these areas will result in a game over. \n");
    printf("\t4. If you stumble upon an unstable configuration of an atom, it will be displayed in the info section above. \n");
    printf("\t5. The decayed particles will be released from your body where it may hit you. \n");
    system("pause");
    system("cls");
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
            instructions();
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
