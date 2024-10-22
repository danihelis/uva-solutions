/* 11946
 * Code Number
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

char decode[] = "OIZEASGTBP";

/* Main function */
int main() {
    char symbol;
    assert(scanf("%*d ") != EOF);
    while ((symbol = getchar()) != EOF) {
        if (isdigit(symbol))
            putchar(decode[symbol - '0']);
        else
            putchar(symbol);
    }
    return EXIT_SUCCESS;
}
