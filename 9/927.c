/* 927
 * Integer Sequences from Addition of Terms
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COEF    21

/* Main function */
int main() {
    int tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        long coef[MAX_COEF], p, n, d, k, i, t, value;
        assert(scanf("%ld", &p) != EOF);
        for (i = 0; i <= p; i++)
            assert(scanf("%ld", &coef[i]) != EOF);
        assert(scanf("%ld %ld", &d, &k) != EOF);
        n = sqrt(k * 2.0 / d);
        if (d * n * (n + 1) / 2 < k)
            n++;
        for (value = 0, t = 1, i = 0; i <= p; i++, t *= n)
            value += coef[i] * t;
        printf("%ld\n", value);
    }
    return 0;
}
