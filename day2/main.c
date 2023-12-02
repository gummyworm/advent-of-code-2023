#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char line[256];

	FILE *f = fopen("input.txt", "r");
	int sum = 0;

	while(fgets(line, 256, f)) {
		char cols[3][10];
		int cnts[3];
		char *game;
		int id;
		int maxr = 0, maxg = 0, maxb = 0;

		sscanf(line, "Game %d: ", &id);
		game = strtok(strchr(line, ':')+1, ";");

		while(game) {
			int matched = sscanf(game, "%d %s %d %s %d %s", 
				&cnts[0], cols[0], &cnts[1], cols[1], &cnts[2], cols[2]);
			for(int i = 0; i < matched/2; i++) {
				int cnt = cnts[i];
				switch (cols[i][0]) {
					case 'r':
						if (cnt > maxr) maxr = cnt;
						break;
					case 'g':
						if (cnt > maxg) maxg = cnt;
						break;
					case 'b':
						if (cnt > maxb) maxb = cnt;
						break;
				}
			}
			game = strtok(NULL, ";");
		}
		sum += maxr*maxg*maxb;
	}
	printf("sum: %d\n", sum);
}
