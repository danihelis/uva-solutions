/* 725
 * Division
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  10
#define MAX_NUMBERS 5
#define MAXIMUM     98765

int minimum_factor[MAX_DIGITS] = {10000, 1000, 100, 10, 1};
char used[MAX_DIGITS];
int n;

/* Check whether the multiple is comprised of non used numbers */
int use_only_remains(int value) {
    char remains[MAX_DIGITS];
    int i;
    memcpy(remains, used, MAX_DIGITS);
    for (i = 0; i < MAX_NUMBERS; i++, value /= 10) {
        int digit = value % 10;
        if (remains[digit]) {
            return 0;
        }
        remains[digit] = 1;
    }
    return 1;
}

/* Search recursively for pairs of five unique digits */
int search(int level, int value) {
    int i, solution, new_value;
    if (level >= MAX_NUMBERS) {
        if (use_only_remains(value * n)) {
            printf("%05d / %05d = %d\n", value * n, value, n);
            return 1;
        }
        return 0;
    }
    for (i = 0, solution = 0; i < MAX_DIGITS; i++) {
        if (!used[i]) {
            new_value = value * 10 + i;
            if (new_value * minimum_factor[level] * n > MAXIMUM) {
                break;
            }
            used[i] = 1;
            solution |= search(level + 1, new_value);
            used[i] = 0;
        }
    }
    return solution;
}

/* Main function */
int main() {
    int first = 1;
    while (scanf("%d", &n) != EOF && n > 0) {
        (first ? first = 0 : printf("\n"));
        memset(used, 0, MAX_DIGITS);
        if (!search(0, 0)) {
            printf("There are no solutions for %d.\n", n);
        }
    }
    return 0;
}
