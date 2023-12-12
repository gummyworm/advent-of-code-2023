#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* top 3 bits are the type of hand */
#define FIVE_OF_A_KIND  ((uint64_t)7<<61)
#define FOUR_OF_A_KIND  ((uint64_t)6<<61)
#define FULL_HOUSE      ((uint64_t)5<<61)
#define THREE_OF_A_KIND ((uint64_t)4<<61)
#define TWO_PAIR        ((uint64_t)3<<61)
#define ONE_PAIR        ((uint64_t)2<<61)
#define HIGH_CARD       ((uint64_t)1<<61)

typedef char hand[5];

int cmp_u64(const void * a, const void * b) {
	uint64_t a64 = *(uint64_t*)a;
	uint64_t b64 = *(uint64_t*)b;
	if (a64 < b64)return -1;
	else if (a64 > b64) return 1;
	return 0;
}

const uint8_t cards[] = {'J','2','3','4','5','6','7','8','9','T','Q','K','A'};

int rank_card(uint8_t card) {
	for(int i = 0; i < sizeof(cards); ++i)
		if (card == cards[i])
			return i+1;
	return -1;
}

uint64_t rank_hand(hand h) {
	uint8_t vals[13];
	int type = 0;
	uint64_t result = 0;
	int pair_found = 0;
	int trio_found = 0;

	memset(vals, 0, sizeof(vals));
	for (int i = 0; i < 5; ++i) {
		uint64_t rank = rank_card(h[i]);
		vals[rank-1]++;
		result |= rank << (12+(4*5)-i*4);
	}

	int jokers = vals[0];
	if (jokers >= 4)
		return FIVE_OF_A_KIND | result;

	for (int i = 1; i < 13; ++i) {
		/* 5 of a kind? */
		if (vals[i] == 5)
			return FIVE_OF_A_KIND | result;
		else if (vals[i] == 4) {
			if (jokers > 0)
				return FIVE_OF_A_KIND | result;
			return FOUR_OF_A_KIND | result;
		}
		else if (vals[i] == 3) {
			if (jokers == 2)
				return FIVE_OF_A_KIND | result;
			if (jokers == 1)
				return FOUR_OF_A_KIND | result;
			if (pair_found)
				return FULL_HOUSE | result;
			trio_found++;
		}
		else if (vals[i] == 2) {
			if (jokers == 3) 
				return FIVE_OF_A_KIND | result;
			if (jokers == 2)
				return FOUR_OF_A_KIND | result;
			if (jokers == 1 && pair_found)
				return FULL_HOUSE | result;
			if (trio_found)
				return FULL_HOUSE | result;
			pair_found++;
		}
	}

	if (jokers == 3)
		return FOUR_OF_A_KIND | result;
	if (trio_found || jokers == 2)
		return THREE_OF_A_KIND | result;

	if (jokers == 2)
		return THREE_OF_A_KIND;

	if (pair_found) {
		if (jokers == 1)
			return THREE_OF_A_KIND | result;
		if (pair_found == 1) 
			return ONE_PAIR | result;
		return TWO_PAIR | result;
	}

	if (jokers == 1)
		return ONE_PAIR | result;
	return HIGH_CARD | result;
}

int main(void) {
	int sum = 0;
	uint64_t hands[1000];
	char line[80];
	int num;

	FILE *f = fopen("input.txt", "r");
	for(num = 0; fgets(line, 80, f); ++num) {
		uint64_t bid = atoi(line+6);
		hands[num] = (rank_hand(line)) | bid;
	}

	qsort(hands, num, sizeof(uint64_t), cmp_u64);
	for (int i = 0; i < num; ++i) {
		sum += (i+1) * (int)(hands[i] & 0x3ff);
	}

	printf("%d\n", sum);
	return fclose(f);
}
