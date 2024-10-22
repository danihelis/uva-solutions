/* 11480
 * Jimmy's Balls
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int test = 0;
    long n;
    while (scanf("%ld", &n) != EOF && n > 0) {
        long m = (n - 2) / 3, n1, n2, result;
        n1 = m / 2, n2 = (m + 1) / 2;
        result = n1 * (n / 2) - 3 * n1 * (n1 + 1) / 2 - (n % 2 == 0 ? n1 : 0)
            + n2 * (n / 2) - 3 * n2 * (n2 + 1) / 2 + n2;
        printf("Case %d: %ld\n", ++test, result);
    }
    return EXIT_SUCCESS;
}
