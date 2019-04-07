// _c for cartesian
// modified calls of functions in console.h adjusted for the Cartesian coordinate system
#include "console.h"

const int X_COORD = 0;
const int Y_COORD = 1;
int getRowCount(){
	int rows, cols;
	getConsoleWindowSize(&rows, &cols);
	return rows;
}

int getColCount(){
	int rows, cols;
	getLargestWindowSize(&rows, &cols);
	return cols;
}

int toConsoleCoords(int cartesianCoord){
	return (getRowCount() - cartesianCoord) * 2;
}

int toCartesian(int consoleCoord){
	return consoleCoord - getRowCount();
}
int putxy_c(int x, int y, int color, const char *s){
	y = toConsoleCoords(y);
	return putxy(x, y, color, s);	
}

int gotoxy_c(int x, int y){
	y = toConsoleCoords(y);
	return gotoxy(x, y);
}

char getConsoleChar_c(int x, int y){
	y = toConsoleCoords(y);
	return getConsoleChar(x, y);
}
