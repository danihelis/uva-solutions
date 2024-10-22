/* 11900
 * Boiled Eggs
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   30

/* Compare integers */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Main function */
int main() {
    int num_tests, test;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, n, p, q, t, w[MAX_N];
        assert(scanf("%d %d %d", &n, &p, &q) == 3);
        for (i = 0; i < n; i++)
            assert(scanf("%d", &w[i]) == 1);
        qsort(w, n, sizeof (int), compare);
        for (i = t = 0; i < n && i < p && t <= q; i++)
            t += w[i];
        if (t > q)
            i--;
        printf("Case %d: %d\n", test, i);
    }
    return EXIT_SUCCESS;
}
