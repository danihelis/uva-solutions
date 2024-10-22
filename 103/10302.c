/* 10302
 * Summation of Polynomials
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SQ(x)   ((x) * (x))

/* Main function */
int main() {
    long n, r;
    while (scanf("%ld", &n) != EOF) {
        r = SQ(n) * SQ(n + 1) / 4;
        printf("%ld\n", r);
    }
    return 0;
}
