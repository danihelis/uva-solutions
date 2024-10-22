/* 10056
 * What is the Probability ?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define EPSILON     1e-10
#define ZERO(a, b)  (fabs((a) - (b)) < EPSILON)

/* Probability of winning:
 * Round 1: P[1] = (1 - p)^(i - 1) · p
 * Round 2: P[2] = (1 - p)^(n + i - 1) · p = P[1] · (1 - p)^n
 * ...
 * Round k: P[k] = (1 - p)^(n·(k - 1) + i - 1) · p = P[k-1] · (1 - p)^n
 */

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        int i, n;
        double p, last, win, p_round, p_lose;
        assert(scanf("%d %lf %d", &n, &p, &i) != EOF);
        p_round = pow(1 - p, i - 1) * p, p_lose = pow(1 - p, n);
        win = p_round;
        do {
            last = win;
            p_round *= p_lose; 
            win += p_round;
        } while (!ZERO(last, win));
        printf("%.4f\n", win);
    }
    return EXIT_SUCCESS;
}
