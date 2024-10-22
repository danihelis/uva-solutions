/* 12068
 * Harmonic Mean
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

typedef struct {
    long num, den;
} frac_t;

/* Greatest common divisor */
long gcd(long a, long b) {
    while (b > 0) {
        long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/* Normalize fraction */
frac_t normalize(frac_t f) {
    long g = gcd(f.num, f.den);
    f.num /= g, f.den /= g;
    return f;
}

/* Sum fractions */
frac_t sum(frac_t a, frac_t b) {
    frac_t res;
    res.num = a.num * b.den + b.num * a.den;
    res.den = a.den * b.den;
    return normalize(res);
}

/* Divive a number by a fraction */
frac_t divide(int a, frac_t b) {
    frac_t res;
    res.num = b.den * a, res.den = b.num;
    return normalize(res);
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, n;
        frac_t mean = {0, 1}, input = {1, 0};
        assert(scanf("%d", &n) == 1);
        for (i = 0; i < n; i++) {
            assert(scanf("%ld", &input.den) == 1);
            mean = sum(mean, input);
        }
        mean = divide(n, mean);
        printf("Case %d: %ld/%ld\n", test, mean.num, mean.den);
    }
    return EXIT_SUCCESS;
}
