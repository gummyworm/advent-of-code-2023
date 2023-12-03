#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define W 140
#define H 140

int issym(char c) { return c != '.' && !isdigit(c); }

int ispart(char engine[H][W+40], int row, int start, int stop) {
	if (start < 0) start = 0;
	if (stop >= W) stop = W-1;

	// row-1
	if (row > 0)
		for(int i = start; i <= stop; ++i)
			if(issym(engine[row-1][i])) 
				return 1;
	// row+1
	if(row < (H-1)) 
		for(int i = start; i <= stop; ++i) 
			if(issym(engine[row+1][i])) 
				return 1;
	// same row
	if (start >= 0 && issym(engine[row][start])) return 1;
	if (stop < W && issym(engine[row][stop])) return 1;
	return 0;
}

int main(void) {
	int sum = 0;
	char engine [H][W+40];

	FILE *f = f = fopen("input.txt", "r");
	for(int i = 0; fgets(engine[i], W+40, f); i++) ;
	fclose(f);

	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			int start, stop;
			while(j < W && !isdigit(engine[i][j])) ++j;
			if (j >= W)
				break;
			start = j;
			while(j < W && isdigit(engine[i][j])) ++j;
			stop = j;

			if (ispart(engine, i, start-1, stop))
				sum += atoi(engine[i]+start);
		}
	}
	printf("sum: %d\n", sum);
	return 0;
}
