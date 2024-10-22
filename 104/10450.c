/* 10450
 * World Cup Noise
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   51

/* Main function */
int main() {
    long fib[MAX_N];
    int i, test, num_tests;
    fib[0] = 1, fib[1] = 2;
    for (i = 2; i < MAX_N; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        assert(scanf("%d", &i) == 1);
        printf("Scenario #%d:\n%ld\n\n", test, fib[i]);
    }
    return EXIT_SUCCESS;
}
