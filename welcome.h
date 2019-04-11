#define WELCOME_SCREEN_SIZE 500
#include "fractals.h"



void welcomePage(){

    printf("$$$$$$$\\                                        $$\\                       $$\\     $$\\    $$$$$$\\  \n$$  __$$\\                                       $$ |                    $$$$ |  $$$$ |  $$  __$$\\\n$$ |  $$ | $$$$$$\\   $$$$$$$\\  $$$$$$\\        $$$$$$\\    $$$$$$\\        \\_$$ |  \\_$$ |  $$ /  $$ |\n$$$$$$$  | \\____$$\\ $$  _____|$$  __$$\\       \\_$$  _|  $$  __$$\\         $$ |    $$ |   $$$$$$  |\n$$  __$$<  $$$$$$$ |$$ /      $$$$$$$$ |        $$ |    $$ /  $$ |        $$ |    $$ |  $$  __$$<\n$$ |  $$ |$$  __$$ |$$ |      $$   ____|        $$ |$$\\ $$ |  $$ |        $$ |    $$ |  $$ /  $$ |\n$$ |  $$ |\\$$$$$$$ |\\$$$$$$$\\ \\$$$$$$$\\         \\$$$$  |\\$$$$$$  |      $$$$$$\\ $$$$$$\\ \\$$$$$$  |\n\\__|  \\__| \\_______| \\_______| \\_______|         \\____/  \\______/       \\______|\\______| \\______/");
    printf("\n\n\nPress any key to continue...");
    printf("\n");
    setScreenSize(WELCOME_SCREEN_SIZE, WELCOME_SCREEN_SIZE);
    //fernDisplay(100, 10,120000, 10);
    float vertexA[2] = {25,15}, vertexB[2] = {0,80}, vertexC[2] = {60,60};

    sierpinskisTriangle(vertexA, vertexB, vertexC,100000);
    getch();
    system("cls");



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
