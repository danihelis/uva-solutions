/* 12895
 * Armstrong Number
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_DIGITS  10
#define MAX_ORDER   10

/* Main function */
int main() {
    long table[NUM_DIGITS][MAX_ORDER], n, k;
    int i, j;
    for (i = 0; i < NUM_DIGITS; i++)
        for (table[i][0] = i, j = 1; j < MAX_ORDER; j++)
            table[i][j] = i * table[i][j - 1];
    assert(scanf("%*d") != EOF);
    while (scanf("%ld", &n) == 1) {
        int order, seq[MAX_ORDER];
        for (i = 0, k = n; k > 0; i++, k /= 10)
            seq[i] = k % 10;
        order = i;
        for (i = 0, k = 0; i < order && k <= n; i++)
            k += table[seq[i]][order - 1];
        printf("%sArmstrong\n", k == n ? "" : "Not ");
    }
    return EXIT_SUCCESS;
}
