#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
	uint16_t l;
	uint16_t r;
}node;

const int AAA = 0;
const int ZZZ = (25<<10) | (25<<5) | 25;
node nodes[0x10000];

unsigned node_id(char *name) {
	int a = (*name - 'A') << 10;
	int b = (*(name+1) - 'A') << 5;
	int c = *(name+2) - 'A';
	return a | b | c;
}

void node_name(uint16_t id) {
	char a, b, c;

	a = 'A' + ((id >> 10) & 0x1f);
	b = 'A' + ((id >> 5) & 0x1f);
	c = 'A' + (id & 0x1f);
	printf("%c%c%c\n", a, b, c);
}


int main(void) {
	char cmds[1000];
	char line[20];
	int id = -1;
	unsigned long long steps = 0;
	size_t len;

	FILE *f = fopen("input.txt", "r");

	/* parse instructions */
	fgets(cmds, 300, f);

	/* parse nodes */
	while(fgets(line, 20, f)) {
		if (strlen(line) < 17)
			continue;
		nodes[node_id(line)] = (node){
			node_id(line+7),
			node_id(line+12),
		};
	}

	/* follow commands */
	for(id = AAA; id != ZZZ; ){
		for(int i = 0; i < strlen(cmds)-1; ++i) {
			++steps;
			if (cmds[i] == 'L') id = nodes[id].l;
			else if(cmds[i] == 'R') id = nodes[id].r;
			else return -1;

			if (id == ZZZ) break;
		}
	}
	printf("steps: %llu\n", steps);
	return 0;
}
