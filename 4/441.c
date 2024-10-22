/* 441
 * Lotto
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MIN_NUMBERS 6
#define MAX_NUMBERS 12

int number[MAX_NUMBERS];
int num_numbers;

/* Compare two numbers in order to sort them */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Recursively enumerate all permutations */
void print_permutation(int start, int level) {
    static int permutation[MIN_NUMBERS];
    int i;
    if (level >= MIN_NUMBERS) {
        for (i = 0; i < MIN_NUMBERS; i++) {
            printf("%d%c", permutation[i], (i == MIN_NUMBERS - 1 ? '\n' : ' '));
        }
    }
    else {
        assert(start < MAX_NUMBERS);
        for (i = start; i <= level + num_numbers - MIN_NUMBERS; i++) {
            permutation[level] = number[i];
            print_permutation(i + 1, level + 1);
        }
    }
}

/* Main function */
int main() {
    int i, first = 1;
    while (scanf("%d", &num_numbers) != EOF && num_numbers > 0) {
        (first ? first = 0 : printf("\n"));
        for (i = 0; i < num_numbers; i++) {
            assert(scanf("%d", &number[i]) != EOF);
        }
        qsort(number, num_numbers, sizeof (int), compare_int);
        print_permutation(0, 0);
    }
    return 0;
}
