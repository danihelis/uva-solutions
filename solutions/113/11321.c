/* 11321
 * Sort! Sort!! and Sort!!!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   10000

int vector[MAX_N];
int mod;

/* Comparison */
int compare(const void *a, const void *b) {
    int x = * (int *) a, y = * (int *) b;
    if (x % mod != y % mod)
        return (x % mod) - (y % mod);
    else if (abs(x % 2) != abs(y % 2))
        return x % 2 == 0 ? 1 : -1;
    else
        return (x % 2 == 0 ? 1 : -1) * (x < y ? -1 : 1);
}

/* Main function */
int main() {
    int i, n;
    while (scanf("%d %d", &n, &mod) == 2) {
        for (i = 0; i < n; i++)
            assert(scanf("%d", &vector[i]) == 1);
        qsort(vector, n, sizeof (int), compare);
        printf("%d %d\n", n, mod);
        for (i = 0; i < n; i++)
            printf("%d\n", vector[i]);
    }
    return EXIT_SUCCESS;
}
