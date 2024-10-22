/* 11850
 * Alaska
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000
#define DISTANCE    1422
#define MAX_DIST    200

/* Compare */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Main function */
int main() {
    int station[MAX_N], n;
    while (scanf("%d", &n) == 1 && n > 0) {
        int i, possible;
        for (i = 0; i < n; i++)
            assert(scanf("%d", &station[i]) == 1);
        qsort(station, n, sizeof (int), compare);
        for (i = 0, possible = 1; possible && i < n - 1; i++)
            possible = station[i + 1] - station[i] <= MAX_DIST;
        possible &= 2 * (DISTANCE - station[n - 1]) <= MAX_DIST;
        printf("%sPOSSIBLE\n", possible ? "" : "IM");
    }
    return EXIT_SUCCESS;
}
