#include "console_c.h"
#include "projection.h"

void Line(int x1, int y1, int x2, int y2, int color, char material){
	float slope = ((float)y2 - (float)y1) / ((float)x2 - (float)x1);
	int y;
	for (int x = x1; x != x2; x++){
		y = slope * (x - x1) + y1;
		putxy_c(x, y, color, &material);
	}	
}


void Line3D(int x1, int y1, int z1, int x2, int y2, int z2, int color, char material){
	int **coords1 = {
	{x1}, {y1}, {z1}
	};
	
	int **coords2 = {
	{x2}, {y2}, {z2}
	};
	
	
}



