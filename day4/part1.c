#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

enum State {
	STATE_INIT,
	STATE_CHOOSE_WINS,
	STATE_GET_HAND
};

int main(void) {
	uint8_t wins[100];
	int num = 0;
	int val = 0;
	int sum = 0;
	int c;
	enum State state = STATE_INIT;

	memset(wins, 0, 100);

	FILE *f = fopen("input.txt", "r");
	while((c = fgetc(f)) != EOF) {
		/* if numeric; update # regardless of state */
		if (isdigit(c)) {
			num = num*10 + (c-'0');
			continue;
		}

		/* handle state changes */ 
		switch(c) {
			case ':': state = STATE_CHOOSE_WINS; break;
			case '|': state = STATE_GET_HAND; break;
		}

		/* handle character for the current state */
		switch (state) {
		case STATE_CHOOSE_WINS:
			if (c == ' ' && num) wins[num] = 1;
			num = 0;
			break;
		case STATE_GET_HAND:
			switch(c) {
			case ' ':
				if (wins[num]) val = (val == 0) ? 1 : val * 2;
				num = 0;
				break;
			case '\n':
				if (wins[num]) val = (val == 0) ? 1 : val * 2;
				sum += val;
				num = val = 0;
				memset(wins, 0, 100);
			default:
				break;
			}
		default:
			break;
		}
	}
	printf("%d\n", sum);
	return fclose(f);
}
