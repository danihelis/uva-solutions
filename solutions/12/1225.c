/* 1225
 * Digit Counting
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10001
#define NUM_DIGITS  10

typedef int count_t[NUM_DIGITS];
count_t count[MAX_N];
int last;

/* Count digits up to N */
void count_digits(int n) {
    int i, number;
    for (i = last + 1; i <= n; i++) {
        memcpy(count[i], count[i - 1], sizeof (count_t));
        number = i;
        while (number > 0) {
            int digit = number % 10;
            count[i][digit]++;
            number /= 10;
        }
    }
    last = n;
}

/* Main function */
int main() {
    int i, n, num_tests;
    memset(count[0], 0, sizeof (count_t));
    last = 0;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d", &n) != EOF);
        count_digits(n);
        for (i = 0; i < NUM_DIGITS; i++)
            printf("%d%c", count[n][i], i == NUM_DIGITS - 1 ? '\n' : ' ');
    }
    return EXIT_SUCCESS;
}
