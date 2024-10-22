/* 10110
 * Light, more light
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
    long number;
    while (scanf("%ld", &number) != EOF && number > 0) {
        long root = sqrt(number);
        printf("%s\n", (SQ(root) == number || SQ(root + 1) == number ? "yes" : "no"));
    }
    return 0;
}
