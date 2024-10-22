/* 11830
 * Contract Revision
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
    char digit;
    while (scanf(" %c ", &digit) == 1 && digit != '0') {
        char symbol, nonzero = 0;
        while (scanf("%c", &symbol) == 1 && isdigit(symbol)) {
            if (symbol == '0' && !nonzero)
                continue;
            if (symbol != digit) {
                putchar(symbol);
                nonzero = 1;
            }
        }
        if (!nonzero)
            putchar('0');
        puts("");
    }
    return EXIT_SUCCESS;
}
