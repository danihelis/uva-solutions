/* 11824
 * A Minimum Land Price
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   41
#define LIMIT   5000000

int land[MAX_N], n;

/* Compare integers */
int compare(const void *a, const void *b) {
    return * (int *) b - * (int *) a;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int i, k;
        long cost, p;
        for (n = 0; ; n++) {
            assert(scanf("%d", &land[n]) == 1);
            if (land[n] == 0)
                break;
        }
        qsort(land, n, sizeof (int), compare);
        for (cost = 0, i = 0; i < n && cost <= LIMIT; i++) {
            for (k = 0, p = 1; k <= i && p < LIMIT; k++)
                p *= land[i];
            cost += 2 * p;
        }
        if (cost > LIMIT)
            puts("Too expensive");
        else
            printf("%ld\n", cost);
    }
    return EXIT_SUCCESS;
}
