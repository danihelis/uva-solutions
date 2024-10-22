/* 574
 * Sum It Up
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     12

int number[MAX_NUMBERS], num_numbers;
int permutation[MAX_NUMBERS], num_permutations;

/* Look for a particular permutation that yields the sum */
int find_sum(int index, int sum) {
    int i, last, found_any;
    if (sum == 0) {
        for (i = 0; i < num_permutations; i++) {
            printf("%d%c", permutation[i], i < num_permutations - 1 ? '+' : '\n');
        }
        return 1;
    }
    else if (index >= num_numbers) {
        return 0;
    }
    for (last = 0, found_any = 0; index < num_numbers; index++) {
        if (number[index] != last && number[index] <= sum) {
            last = number[index];
            permutation[num_permutations++] = last;
            found_any |= find_sum(index + 1, sum - last);
            num_permutations--;
        }
    }
    return found_any;
}

/* Main function */
int main() {
    int i, sum;
    while (scanf("%d %d", &sum, &num_numbers) != EOF && num_numbers > 0) {
        printf("Sums of %d:\n", sum);
        for (i = 0; i < num_numbers; i++) {
            assert(scanf("%d", &number[i]) != EOF);
        }
        num_permutations = 0;
        if (!find_sum(0, sum)) {
            printf("NONE\n");
        }
    }
    return 0;
}
