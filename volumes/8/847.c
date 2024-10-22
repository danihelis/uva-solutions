/*
 * 847
 * A Multiplication Game
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
    unsigned long number;

    while (scanf("%lu", &number) != EOF) {
        while (number > 9) {
            number = number / 18 + (number % 18 == 0 ? 0 : 1); /* ceil */
        }
        printf("%s wins.\n", (number != 1 ? "Stan" : "Ollie"));
    }
    return 0;
}
