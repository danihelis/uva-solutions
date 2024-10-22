/* 834
 * Continued Fractions
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
    int num, den;
    while (scanf("%d %d", &num, &den) != EOF) {
        char first = 1;
        assert(num % den != 0);
        printf("[%d", num / den);
        while (num % den != 0) {
            int k = num % den;
            num = den;
            den = k;
            printf("%c%d", (first ? ';' : ','), num / den);
            first = 0;
        }
        printf("]\n");
    }
    return 0;
}
