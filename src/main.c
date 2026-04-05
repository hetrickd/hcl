#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NUM 6 // not safe to raise unless sort.c is rewritten
#define EXPR_MAXLEN 30
#define HT_SIZE 8191

uint32_t bad_branches[HT_SIZE];

// A number and an expression that makes it
typedef struct {
	float value;
	char expr[EXPR_MAXLEN];
} NumberExpr;

// Fowler-Noll-Vo hash (assumes sorted)
uint32_t fnv(int values[], int n) {
	uint32_t hash = 2166136261U;
	for (int i = 0; i < n; i++) {
		hash ^= (uint32_t)values[i];
		hash *= 16777619U;
	}
	return hash;
}

bool seen_before(uint32_t hash) {
	int idx = hash % HT_SIZE;
	uint32_t bitmask = 1 << (hash % 32);

	if (bad_branches[idx] & bitmask) {
		return true;
	}
	return false;
}

void bad_branch(uint32_t hash) {
	int idx = hash % HT_SIZE;
	uint32_t bitmask = 1 << (hash % 32);

	bad_branches[idx] |= bitmask;
}

// forward decl, see sort.c
void sort(int* arr, int n);

void build_expr(char* result, const char* a, const char* b, const char* op) {
	strcpy(result, "(");
	strcat(result, a);
	strcat(result, op);
	strcat(result, b);
	strcat(result, ")");
}

char* solve(NumberExpr nums[], int n, int target) {
	if (n == 1) {
		if (nums[0].value == target) {
			char* result = malloc(strlen(nums[0].expr) + 1);
			strcpy(result, nums[0].expr);
			return result;
		} else {
			// bad leaf, backtrack one step
			return NULL;
		}
	}

	int values[MAX_NUM];
	for (int i = 0; i < n; i++) {
		values[i] = nums[i].value;
	}
	sort(values, n);
	uint32_t h = fnv(values, n);
	if (seen_before(h)) {
		return NULL;
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			NumberExpr a = nums[i];
			NumberExpr b = nums[j];

			NumberExpr rest[MAX_NUM - 1];
			int idx = 0;
			for (int k = 0; k < n; k++) {
 				if (k != i && k != j) {
					rest[idx++] = nums[k];
				}
			}

			NumberExpr branches[6];
			int bidx = 0;

			branches[bidx].value = a.value + b.value;
			build_expr(branches[bidx].expr, a.expr, b.expr, "+");
			bidx++;

			branches[bidx].value = a.value * b.value;
			build_expr(branches[bidx].expr, a.expr, b.expr, "*");
			bidx++;

			branches[bidx].value = a.value - b.value;
			build_expr(branches[bidx].expr, a.expr, b.expr, "-");
			bidx++;

			branches[bidx].value = b.value - a.value;
			build_expr(branches[bidx].expr, b.expr, a.expr, "-");
			bidx++;

			if (b.value != 0) {
				branches[bidx].value = a.value / b.value;
				build_expr(branches[bidx].expr, a.expr, b.expr, "/");
				bidx++;
			}

			if (a.value != 0) {
				branches[bidx].value = b.value / a.value;
				build_expr(branches[bidx].expr, b.expr, a.expr, "/");
				bidx++;
			}

			// recurse for each branch
			for (int k = 0; k < bidx; k++) {
				rest[idx] = branches[k];
				char* result = solve(rest, idx + 1, target);
				if (result != NULL) {
					return result;
				}
			}
			bad_branch(h);
		}
	}

	return NULL;
}


int main() {
	char line[256];

	if (!fgets(line, sizeof(line), stdin)) {
		fprintf(stderr, "Failed to read input\n");
		return 1;
	}

	char* sep = strchr(line, ';');
	if (!sep) {
		fprintf(stderr, "Input format: TARGET; N1 N2 ...\n");
		return 2;
	}

	*sep = '\0';
	int target = atoi(line);

	NumberExpr numbers[MAX_NUM];
	int n = 0;

	// parse nums after the semicolon
	char* tok = strtok(sep + 1, " \t\n");
	while (tok && n < MAX_NUM) {
		int val = atoi(tok);
		snprintf(numbers[n].expr, EXPR_MAXLEN, "%d", val);
		numbers[n].value = (int16_t)val;
		n++;
		tok = strtok(NULL, " \t\n");
	}

	if (n == 0) {
		fprintf(stderr, "No numbers provided\n");
		return 3;
	}

	char* solution = solve(numbers, n, target);
	if (solution) {
		printf("%s\n", solution);
		free(solution);
	} else {
		fprintf(stderr, "No solution found\n");
		return 4;
	}

	return 0;
}
