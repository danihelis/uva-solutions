/* 11489
 * Integer Game
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_DIGITS  9
#define MAX_STRING  1002

/* Compute whether it's is possible to win the game */
int can_win(int digits[], int sum) {
    int i, win;
    if (sum == 0)
        return 0;
    for (i = 0; i < NUM_DIGITS; i++)
        if (digits[i] > 0 && (sum - i - 1) % 3 == 0) {
            int bk = digits[i];
            digits[i] = (bk - 1) % 2;
            win = can_win(digits, sum - i - 1);
            digits[i] = bk;
            if (!win)
                return 1;
        }
    return 0;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        int sum, digits[NUM_DIGITS];
        char input[MAX_STRING], *d;
        assert(scanf(" %s", input));
        memset(digits, 0, NUM_DIGITS * sizeof (int));
        for (d = input, sum = 0; *d != 0; d++)
            sum += *d - '0', digits[*d - '1']++;
        printf("Case %d: %c\n", test + 1, can_win(digits, sum) ? 'S' : 'T');
    }
    return EXIT_SUCCESS;
}
