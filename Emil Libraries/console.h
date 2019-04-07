/*************************************************
  Simple Console Library
  
  prepared by J. Catalan for LBYEC71/LBYEC72
*************************************************/

#include <windows.h>

// text color constants (low intensity)
const WORD TLRED = FOREGROUND_RED;
const WORD TLGREEN = FOREGROUND_GREEN;
const WORD TLBLUE = FOREGROUND_BLUE;
const WORD TLYELLOW = FOREGROUND_GREEN | FOREGROUND_RED;
const WORD TLBLUEGREEN = FOREGROUND_BLUE|FOREGROUND_GREEN;
const WORD TLVIOLET = FOREGROUND_BLUE|FOREGROUND_RED;
const WORD TLWHITE = FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN;

// text color constants (high intensity)
const WORD TRED = TLRED|FOREGROUND_INTENSITY;
const WORD TGREEN = TLGREEN|FOREGROUND_INTENSITY;
const WORD TBLUE = TLBLUE|FOREGROUND_INTENSITY;
const WORD TBLUEGREEN = TLBLUEGREEN|FOREGROUND_INTENSITY;
const WORD TYELLOW = TLYELLOW|FOREGROUND_INTENSITY;
const WORD TVIOLET = TLVIOLET|FOREGROUND_INTENSITY;
const WORD TWHITE = TLWHITE|FOREGROUND_INTENSITY;
const WORD TGRAY = TLWHITE;
const WORD TBLACK = 0;

// background color constants (low Intensity)
const DWORD BLRED = BACKGROUND_RED|0x0100;
const DWORD BLGREEN = BACKGROUND_GREEN|0x0100;
const DWORD BLBLUE = BACKGROUND_BLUE|0x0100;
const DWORD BLYELLOW = BACKGROUND_RED|BACKGROUND_GREEN|0x0100;
const DWORD BLBLUEGREEN = BACKGROUND_BLUE|BACKGROUND_GREEN|0x0100;
const DWORD BLVIOLET = BACKGROUND_BLUE|BACKGROUND_RED|0x0100;
const DWORD BLWHITE = BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_GREEN|0x0100;

// background color constants (low Intensity)
const DWORD BRED = BLRED|BACKGROUND_INTENSITY;
const DWORD BGREEN = BLGREEN|BACKGROUND_INTENSITY;
const DWORD BBLUE = BLBLUE|BACKGROUND_INTENSITY;
const DWORD BYELLOW = BLYELLOW|BACKGROUND_INTENSITY;
const DWORD BBLUEGREEN = BLBLUEGREEN|BACKGROUND_INTENSITY;
const DWORD BVIOLET = BLVIOLET|BACKGROUND_INTENSITY;
const DWORD BWHITE = BLWHITE|BACKGROUND_INTENSITY;
const DWORD BGRAY = BLWHITE;
const DWORD BBLACK = 0x0100;

// sets the color of text to be printed next
// Ex. textcolor(TRED);
int textcolor(DWORD attr);

// places the cursor at position indicated by column (X) and line (Y)
// Ex. gotoxy(2,10);  -- for cursor at line 3 and column 11
int gotoxy(int column, int line );

// returns the X position of the cursor
int whereX();

// returns the Y position of the cursor
int whereY();

// returns the character displayed at position (x,y)
// c = getConsoleChar(0,0);  -- gets the character at the 1st line and 1st column
char getConsoleChar(int x, int y);

// determines the maximum window size available for the screen in terms of number of
//    (number of rows) x (number of cols) of characters that can be displayed.
//
// Ex. getLargestWindowSize(&r,&c);  -- stores the row size in r, the column size in c
void getLargestWindowSize(int *rows, int *cols);

// sets the window size to rows x cols
// Ex. setWindowSize(10,40); -- sets the 
int setWindowSize(int rows, int cols);

// sets the background color
// Ex. setBackgrounColor(BYELLOW);
void setBackgroundColor(DWORD color);

// gets the console windows size (rows, cols)
// Ex. getConsoleWindowSize(&rows,&cols);
void getConsoleWindowSize(int *rows, int *cols);

// sets the screen size to rows x cols 
// screen size can be larger than window size, in
// which case, scrollbars will appear
// Ex. setScreenSize  
int setScreenSize(int rows, int cols);

// set cursor size and visibility property
//   size is between 1-100 which represents the
//      size in percent of the character height.
//   visibility is set to 0 for non-visible, 
//      or 1 for visible 
// Ex. setCursorProperty(50,1);
int setCursorProperty(int size, int visibility);

// puts the string s  starting at y row, x col position
int putxy(int x, int y, int color, const char *s);
