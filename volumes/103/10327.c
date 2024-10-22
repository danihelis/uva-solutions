/* 10327
 * Flip Sort
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     1000

/* Main function */
int main() {
    int n, vector[MAX_DIM];
    while (scanf("%d", &n) != EOF) {
        int i, j, total;
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &vector[i]) != EOF);
        }
        for (i = 0, total = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                if (vector[j] > vector[j + 1]) {
                    int swap = vector[j];
                    vector[j] = vector[j + 1];
                    vector[j + 1] = swap;
                    total++;
                }
            }
        }
        printf("Minimum exchange operations : %d\n", total);
    }
    return 0;
}
