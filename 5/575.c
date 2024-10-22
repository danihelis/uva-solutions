/* 575
 * Skew Binary
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  40

/* Main function */
int main() {
    char digit[MAX_STRING];
    while (scanf(" %s", digit) != EOF) {
        long i, n, p;
        for (i = strlen(digit) - 1, n = 0, p = 2; i >= 0; i--, p <<= 1) {
            if (digit[i] != '0') {
                n += (digit[i] - '0') * (p - 1);
            }
        }
        if (n == 0) {
            break;
        }
        printf("%ld\n", n);
    }
    return 0;
}
