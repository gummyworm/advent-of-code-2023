#include <stdint.h>
#include <stdio.h>

#define W 140
#define H 140

typedef struct {
	uint64_t x;
	uint64_t y;
}galaxy;

char map[H][W+2];

uint64_t dist(galaxy a, galaxy b) {
	uint64_t d = 0;
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
	galaxy galaxies[500];
	int num = 0;

	/* read image */
	for (int y = 0; fgets(map[y], W+2, f); ++y) ;

	/* calc galaxy positions  */
	uint64_t y_expand = 0;
	for (uint64_t y = 0; y < H; ++y) {
		uint64_t x_expand = 0;
		if (row_empty(y)) {
			y_expand += 1000000-1;
			continue;
		}
		for (uint64_t x = 0; x < W; ++x) {
			if (col_empty(x))
				x_expand += 1000000-1;
			else if (map[y][x] != '.')
				galaxies[num++] = (galaxy){x+x_expand, y+y_expand};
		}
	}

	uint64_t sum = 0;
	for (int i = 0; i < num; ++i)
		for (int j = i+1; j < num; ++j)
			sum += dist(galaxies[i], galaxies[j]);

	printf("%llu\n", sum);
	return fclose(f);
}
