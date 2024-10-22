/* 11401
 * Triangle Counting
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    long n;
    while (scanf("%ld", &n) != EOF && n >= 3) {
        long r, p = n >> 1;
        r = (4 * p * p - 9 * p + 5) * p / 6 + (n % 2 == 1 ? (p + 1) * (p - 2) + 2 : 0);
        printf("%ld\n", r);
    }
    return 0;
}
