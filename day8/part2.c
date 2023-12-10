#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
	uint16_t l;
	uint16_t r;
	int visited;
}node;
node nodes[0x10000];

unsigned node_id(char *name) {
	int a = (*name - 'A') << 10;
	int b = (*(name+1) - 'A') << 5;
	int c = *(name+2) - 'A';
	return a | b | c;
}

void update_ids(char cmd, int num, node *nodes, int *ids) {
	for(int i = 0; i < num; ++i) {
		int id = ids[i];
		if (cmd == 'L') ids[i] = nodes[id].l;
		else if(cmd == 'R') ids[i] = nodes[id].r;
		else exit(-1);
	}
}

unsigned long long gcd(unsigned long long a, unsigned long long b) { 
	if (b == 0) return a; 
	return gcd(b, a % b);
} 

unsigned long long lcm(int vals[], int n) {
	unsigned long long m = vals[0];
	for (int i = 1; i < n; ++i) {
		m = m * vals[i] / gcd(m, vals[i]);
	}
	return m;
}

int main(void) {
	char cmds[1000];
	char line[20];
	int ids[10];
	int zs[10];

	int num_z = 0;
	int num = 0;
	unsigned long long steps = 0;

	FILE *f = fopen("input.txt", "r");

	/* parse instructions */
	fgets(cmds, 300, f);

	memset(nodes, 0, sizeof(node)*0x10000);

	/* parse nodes */
	while(fgets(line, 20, f)) {
		if (strlen(line) < 17)
			continue;
		uint16_t id = node_id(line);
		nodes[id] = (node){
			node_id(line+7),
			node_id(line+12),
			0
		};
		if ((id & 0x1f) == 0)
			ids[num++] = id;
		else if ((id & 0x1f) == 25)
			++num_z;
	}

	/* follow commands until we've visited each ..Z  */
	for(int found = 0; found < num_z; ) {
		for(int i = 0; i < strlen(cmds)-1; ++i) {
			++steps;
			update_ids(cmds[i], num, nodes, ids);

			for (int i = 0; i < num; ++i) {
				if (!nodes[ids[i]].visited) {
					nodes[ids[i]].visited++;
					if ((ids[i] & 0x1f) == 25)
						zs[found++] = steps;
				}
			}
		}
	}
	printf("%llu\n", lcm(zs, num_z));
	return 0;
}
