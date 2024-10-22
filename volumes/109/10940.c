/* 10940
 * Throwing cards away II
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX     500000

/* Main function */
int main() {
    int n, i, t[MAX];
    t[0] = 1, i = 1;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (; i < n; i++)
            t[i] = (t[i / 2] - 1 + (i % 2)) * 2;
        printf("%d\n", t[n - 1]);
    }
    return EXIT_SUCCESS;
}
