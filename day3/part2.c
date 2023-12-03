#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define W 140
#define H 140

int partsfromrow(char engine[H][W+40], int row, int col, int *n) {
	int parsed = 0;
	if (row < 0 || row > H)
		return 0;
	{
		/*
		 * possible digit patterns are:
		 *   [..., ..n, .n., .nn, n.., n.n, nn., nnn]
		 *   of these n.n is 2 numbers others are 1
		*/
		int a = isdigit(engine[row][col-1]);
		int b = isdigit(engine[row][col]);
		int c = isdigit(engine[row][col+1]);
		if (!a && !b && !c)
			return 0;

		if (a && !b && c) {
			*n *= atoi(engine[row] + col+1);
			++parsed;
		} 
		while(col > 0 && isdigit(engine[row][col-1])) --col;
		while(col < W && !isdigit(engine[row][col])) ++col;
		*n *= atoi(engine[row] + col);
		++parsed;
	}
	return parsed;
}

int gearval(char engine[H][W+40], int row, int col) {
	int product = 1;

	int parts = partsfromrow(engine, row-1, col, &product);
	parts += partsfromrow(engine, row, col, &product);
	parts += partsfromrow(engine, row+1, col, &product);
	if (parts != 2)
		return 0;
	return product;
}

int main(void) {
	int sum = 0;
	char engine [H][W+40];

	FILE *f = f = fopen("input.txt", "r");
	for(int i = 0; fgets(engine[i], W+40, f); i++) ;
	fclose(f);

	for(int i = 0; i < H; ++i)
		for(int j = 0; j < W; ++j)
			if (engine[i][j] == '*') 
				sum += gearval(engine, i, j);
	printf("sum: %d\n", sum);
	return 0;
}
