/* 10689
 * Yet another Number Sequence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_M   4

typedef struct {
    int major, minor;
} pair_t;

int masks[MAX_M] = {10, 100, 1000, 10000};

/* Compute F{2n}, F{2n-1} recursively.
 *      F{2n-1} = F{n}² + F{n-1}²
 *      F{2n}   = (2·F{n-1} + F{n})·F{n}
 */
pair_t compute_f2n(int n, int mask) {
    pair_t half, result = {1, 1};
    if (n > 1) {
        int k = n / 2;
        half = compute_f2n(k, mask);
        result.minor = half.minor * half.minor + half.major * half.major;
        result.major = (2 * half.minor + half.major) * half.major;
        result.minor %= mask, result.major %= mask;
        if (n % 2 == 1) {
            pair_t lesser = result;
            result.minor = (lesser.minor + lesser.major) % mask;
            result.major = (lesser.major + result.minor) % mask;
        }
    }
    return result;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int a, b, n, m, value, mask;
        pair_t f2n;
        assert(scanf("%d %d %d %d", &a, &b, &n, &m) != EOF);
        if (n < 2) {
            printf("%d\n", n == 0 ? a : b);
            continue;
        }
        mask = masks[--m];
        f2n = compute_f2n(n / 2, mask);
        if (n % 2 == 1) {
            value = (f2n.major + f2n.minor) % mask;
            f2n.minor = f2n.major;
            f2n.major = value;
        }
        value = (f2n.major * b + f2n.minor * a) % mask;
        printf("%d\n", value);
    }
    return EXIT_SUCCESS;
}
