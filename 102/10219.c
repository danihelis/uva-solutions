/* 10219
 * Find the ways !
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

/* Compute log(n! / m!) */
double log_factorial(long n, long m) {
    double result = 0;
    for (m++; m <= n; m++)
        result += log10(m);
    return result;
}

/* Main function */
int main() {
    long n, k, count;
    while (scanf("%ld %ld", &n, &k) != EOF) {
        count = floor(log_factorial(n, MAX(k, n - k)) - 
                log_factorial(MIN(k, n - k), 1)) + 1;
        printf("%ld\n", count);
    }
    return EXIT_SUCCESS;
}
