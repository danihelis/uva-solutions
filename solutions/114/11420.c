/* 11420
 * Chest of Drawers
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       65
#define MAX_SIZE    (MAX_N + 1)

long unlocked[MAX_SIZE][MAX_SIZE], locked[MAX_SIZE][MAX_SIZE];

/* Compute dynamic programming table:
 *      u(1,s) = 2 if s = 0 else 0
 *      l(1,s) = 1 if s = 0 or 1 else 0
 *      u(n,s) = u(n-1,s) + l(n-1,s)
 *      l(n,s) = u(n-1,s) + l(n-1,s-1)
 * The answer is l(n,s).
 */
void compute() {
    int n, s;
    for (n = 1; n <= MAX_N; n++) {
        for (s = 0; s <= MAX_N; s++) {
            if (n == 1) {
                unlocked[n][s] = s == 0 ? 2 : 0;
                locked[n][s] = s == 0 || s == 1 ? 1 : 0;
            } else {
                unlocked[n][s] = unlocked[n - 1][s] + locked[n - 1][s];
                locked[n][s] = unlocked[n - 1][s] + 
                        (s > 0 ? locked[n - 1][s - 1] : 0);
            }
        }
    }
}

/* Main function */
int main() {
    int n, s;
    compute();
    while (scanf("%d %d", &n, &s) == 2 && n >= 1) {
        printf("%ld\n", locked[n][s]);
    }
    return EXIT_SUCCESS;
}
