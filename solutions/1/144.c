/* 144
 * Student Grants
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   25
#define TOTAL   40

#define MIN(x, y)       ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int wallet[MAX_N], queued[MAX_N];
    int i, n, k, withdraw, output, next, out;
    while (scanf("%d %d", &n, &k) != EOF && n > 0) {
        for (i = 0; i < n; i++)
            wallet[i] = 0, queued[i] = 1;
        for (i = 0, output = 0, next = 0, out = 0; out < n; i = (i + 1) % n)
            if (queued[i]) {
                if (output == 0) {
                    output = next + 1;
                    next = (next + 1) % k;
                }
                withdraw = MIN(TOTAL - wallet[i], output);
                wallet[i] += withdraw;
                output -= withdraw;
                if (wallet[i] == TOTAL) {
                    queued[i] = 0, out++;
                    printf("%3d", i + 1);
                }
            }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
