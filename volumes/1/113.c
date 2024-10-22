/* 113
 * Power of Cryptography
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  101
#define MAX_STRING  (MAX_DIGITS + 2)

/* Main function */
int main() {
    int k, size, result;
    char bigint[MAX_STRING];
    double value;
    bigint[0] = '.';
    while (scanf("%d %s", &k, bigint + 1) != EOF) {
        assert(sscanf(bigint, "%lf", &value) == 1);
        size = strlen(bigint) - 1;
        value = size + log10(value);
        value = pow(10, value / k);
        result = (int) value;
        if ((result % 2) != ((bigint[size] - '0') % 2)) {
            result++;
        }
        printf("%d\n", result);
    }
    return 0;
}
