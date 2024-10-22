/* 371
 * Ackermann Functions
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

/* Determine the cycle-length of a number */
int cycle(long n) {
    int steps = 0;
    do {
        n = (n % 2 == 0 ? n / 2 : 3 * n + 1);
        steps++;
    } 
    while (n > 1);
    return steps;
}

/* Main function */
int main() {
    long i, j, n, best;
    while (scanf("%ld %ld", &i, &j) != EOF && (i > 0 || j > 0)) {
        int maximum;
        for (n = MIN(i, j), maximum = 1, best = 1; n <= MAX(i, j); n++) {
            int length = cycle(n);
            if (length > maximum) {
                maximum = length, best = n;
            }
        }
        printf("Between %ld and %ld, %ld generates the longest sequence of %d values.\n", 
                MIN(i, j), MAX(i, j), best, maximum);
    }
    return 0;
}
