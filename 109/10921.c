/* 10921
 * Find the Telephone
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
    char symbol;
    int code;
    while (scanf("%c", &symbol) != EOF) {
        if (isalpha(symbol)) {
            assert(isupper(symbol));
            code = (symbol <= 'R' ? (symbol - 'A') / 3 + 2 : 
                    symbol == 'S' ? 7 : symbol <= 'V' ? 8 : 9);
            printf("%d", code);
        }
        else {
            printf("%c", symbol);
        }
    }
    return 0;
}
