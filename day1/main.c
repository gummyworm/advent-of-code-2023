#include <stdio.h>
#include <string.h>

int val(char *s) {
	const char *strings[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	const int lens[] = {3, 3, 5, 4, 4, 3, 5, 5, 4};

	if (s[0] > '0' && s[0] < ('9'+1)) return s[0] - '0';
	for(int i = 0; i < 9; i++)
		if(strncmp(s, strings[i], lens[i]) == 0) return i+1;
	return -1;
}

int main(void) {
	char line[80];
	int sum, left, right;

	FILE *f = fopen("input.txt", "r");
	for(sum = 0; fgets(line, 80, f); sum += left*10+right) {
		char *cur;
		for(cur = line; *cur; cur++) 
			if ((left = val(cur)) > 0) break; 
		for(cur = line+strlen(line)-1; cur >= line; cur--) 
			if ((right = val(cur)) > 0) break;
	}
	printf("sum: %d\n", sum);
	return fclose(f);
}
