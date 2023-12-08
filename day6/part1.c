#include <stdio.h>

int eval(int time, int dist) {
	int num = 0;
	for (int t = 0; t < time; t++)
		if (t * (time - t) > dist)
			++num;
	return num;
}

int main(void) {
	int race_times[4] = {48,87,69,81};
	int distances[4] = {255,1288,1117,1623};
	int product = 1;

	for (int i = 0; i < 4; i++) 
		product *= eval(race_times[i], distances[i]);
	printf("%d\n", product);
	return 0;
}
