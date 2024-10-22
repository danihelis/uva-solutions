/* 445
 * Marvelous Mazes
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    char symbol;
    int count = 0;
    while (scanf("%c", &symbol) != EOF) {
        if (isdigit(symbol)) {
            count += symbol - '0';
        }
        else if (symbol == '!' || symbol == '\n') {
            printf("\n");
        }
        else {
            if (symbol == 'b') {
                symbol = ' ';
            }
            for (; count > 0; count--) {
                printf("%c", symbol);
            }
        }
    }
    return 0;
}
