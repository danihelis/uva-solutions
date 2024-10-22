/* 10976
 * Fractions Again?!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

/* Main function */
int main() {
    int n, y[MAX_N], x[MAX_N];
    while (scanf("%d", &n) != EOF) {
        int i, total;
        for (i = n + 1, total = 0; i <= 2 * n; i++) {
            int multi = n * i, diff = i - n;
            if (multi % diff == 0) {
                y[total] = i;
                x[total] = multi / diff;
                total++;
            }
        }
        printf("%d\n", total);
        for (i = 0; i < total; i++) {
            printf("1/%d = 1/%d + 1/%d\n", n, x[i], y[i]);
        }
    }
    return EXIT_SUCCESS;
}
