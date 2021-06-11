// ___________ SumToC ____________
// simple backtracking

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sumToC(int *sequence, int C, int n, int sum);

int main()
{
	int C, i;
	printf("Enter a number:\n");
	scanf("%d", &C);

	// array used to store the sequence; 1 = in sequence, 0 = not in sequence
	int *sequence = malloc(sizeof(int) * C);
	for (i = 0; i < C; i++)
		sequence[i] = 0;

	// clock_t begin = clock();
	//
	sumToC(sequence, C, 1, 0);
	//
    // clock_t end = clock();
    // double runtime = (double) (end - begin) / CLOCKS_PER_SEC;
    // printf("Program run time: %f\n", runtime);

    return 0;
}

void sumToC(int *sequence, int C, int n, int sum) {
	// base case: sequence found, print it
	if (sum == C) {
		for (int i = 0; i < n - 1; i++) {
			if (sequence[i] != 0) {
				printf(" %d ", i + 1);
			}
		}
		printf("\n");
		return;
	}
	// case: stop searching if n is beyond C
	else if (n > C)
		return;

	// add current number n if sum + n <= C
	if (sum + n <= C) {
		sequence[n-1] = 1;

		// consider next number n+1
		sumToC(sequence, C, n+1, sum+n);

		// backtrack
		sequence[n-1] = 0;
	}

	// consider next number n+1  without adding current number n
	sumToC(sequence, C, n+1, sum);
}