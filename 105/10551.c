/* 10551
 * Basic Remains
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1010

/* Convert base (from or to b10) */
long convert_base(long value, int b0, int b1) {
    long power, result;
    if (b0 == b1)
        return value;
    for (power = 1, result = 0; value > 0; value /= b1, power *= b0)
        result += (value % b1) * power;
    return result;
}

/* Main function */
int main() {
    int base;
    while (scanf("%d", &base) != EOF && base > 0) {
        long modulo, value;
        char input[MAX_STRING], *c;
        assert(scanf(" %s %ld", input, &modulo) != EOF);
        modulo = convert_base(modulo, base, 10);
        for (value = 0, c = input; *c != 0; c++)
            value = (value * base + *c - '0') % modulo;
        printf("%ld\n", convert_base(value, 10, base));
    }
    return EXIT_SUCCESS;
}
