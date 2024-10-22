/* 11185
 * Ternary
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAXDIGITS   30
#define BASE        3

/* Main function */
int main() {
    int result[MAXDIGITS];
    int number, i;
    while (scanf("%d", &number) != EOF && number >= 0) {
        for (i = 0; number > 0; i++) {
            result[i] = number % BASE;
            number /= BASE;
        }
        if (i == 0) {
            printf("0\n");
        }
        else {
            for (i--; i >= 0; i--) {
                printf("%d", result[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
