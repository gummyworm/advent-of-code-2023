#include <stdio.h>

int eval(unsigned long vel, unsigned long time, unsigned long len) {
	return (vel * (time-vel)) > len ? 1 : 0;
}

unsigned long Bseek(unsigned long time, unsigned long len) {
	long t;
	for (t = time-2; t > 0; --t) {
		/* look for the transition from 1 to 0
		 * 111100
		 *    ^^
		 */
		if (!eval(t+1, time, len))
			if (eval(t, time, len))
				break;
	}
	return t;
}

unsigned long Fseek(unsigned long time, unsigned long len) {
	long t;
	for (t = 0; t < time; ++t) {
		/* look for the transition from 0 to 1
		 * 000111
		 *    ^^
		 */
		if (!eval(t, time, len))
			if (eval(t+1, time, len))
				break;
	}
	return t;
}

int main(void) {
	unsigned long start = Fseek(48876981, 255128811171623);
	unsigned long end = Bseek(48876981, 255128811171623);
	printf("%lu\n", end-start);
	return 0;
}
