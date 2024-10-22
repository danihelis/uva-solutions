/* 12467
 * Secret Word
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000002

char input[MAX_N], best[MAX_N];

/* Find secret word */
void find_secret() {
    int backtrack[MAX_N];
    int i, j, max;
    char *s, *b;

    /* Create a table with values for backtracking */
    i = 0, j = -1;
    backtrack[i] = j;
    while (input[i] != 0) {
        while (j >= 0 && input[i] != input[j]) j = backtrack[j];
        i++, j++;
        backtrack[i] = j;
    }

    /* Match largest reverse substring */
    s = input + strlen(input) - 1, j = 0, max = 0, b = input;
    while (s >= input) {
        while (j >= 0 && *s != input[j]) j = backtrack[j];
        j++;
        if (j > max) b = s, max = j;
        s--;
    }
    strncpy(best, b, max);
    best[max] = 0;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        assert(scanf(" %s", input) == 1);
        find_secret();
        printf("%s\n", best);
    }
    return EXIT_SUCCESS;
}
