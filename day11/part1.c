#include <stdio.h>

#define W 140
#define H 140

typedef struct {
	int x;
	int y;
}galaxy;

char map[H][W+2];

int dist(galaxy a, galaxy b) {
	int d = 0;
	if (a.x > b.x) d = a.x - b.x;
	else d = b.x - a.x;
	if (a.y > b.y) return d + a.y - b.y;
	else return d + b.y - a.y;
}

int col_empty(int col) {
	for(int y = 0; y < H; ++y)
		if (map[y][col] != '.')
			return 0;
	return 1;
}

int row_empty(int row) {
	for(int x = 0; x < W; ++x)
		if (map[row][x] != '.')
			return 0;
	return 1;
}


int main(void) { 
	FILE *f = fopen("input.txt", "r");
	galaxy galaxies[3000];
	int num = 0;

	/* render map */
	for (int y = 0; fgets(map[y], W+2, f); ++y) ;

	/* calc galaxy positions  */
	int y_expand = 0;
	for (int y = 0; y < H; ++y) {
		int x_expand = 0;
		if (row_empty(y))
			y_expand++;
		for (int x = 0; x < W; ++x) {
			if (col_empty(x))
				x_expand++;
			else if (map[y][x] != '.')
				galaxies[num++] = (galaxy){x+x_expand, y+y_expand};
		}
	}

	int sum = 0;
	for (int i = 0; i < num; ++i)
		for (int j = i+1; j < num; ++j)
			if (i != j)
				sum += dist(galaxies[i], galaxies[j]);
	printf("%d\n", sum);
	return fclose(f);
}
