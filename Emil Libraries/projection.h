
#include <stdlib.h>

float** initializeMatrix(int cols, int rows){
	//cols: x-axis
	//rows: y-axis
	
	float **matrix = (float**) malloc(rows * sizeof(float*));
	
	for (int i = 0; i != rows; i++) {
		matrix[i] = (float*) malloc(cols * sizeof(float));
		for (int j = 0; j != cols; j++){
			matrix[i][j] = 0;
		}
	}
	
	return matrix;
}
void matrixMultiply(float **first, int firstCols, int firstRows, float **second, int secondCols, int secondRows, float **answer){
	for (int firstRow = 0; firstRow != firstRows; firstRow++){
		for (int secondCol = 0; secondCol != secondCols; secondCol++){
			for (int firstCol = 0; firstCol != firstCols; firstCol++){
				answer[firstRow][secondCol] += (first[firstRow][firstCol] * second[firstCol][secondCol]);				
			}
		}
	}
}

void projector(float **input, float **output){
	float **projectionMatrix = initializeMatrix(3, 2);

	
	projectionMatrix[0][0] = 1;
	projectionMatrix[1][1] = 1;
	
	
	
	matrixMultiply(projectionMatrix, 3, 2, input, 1, 3, output);
}

