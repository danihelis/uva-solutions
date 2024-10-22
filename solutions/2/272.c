/* 272
 * TEX Quotes
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
    int odd = 1;
    char symbol;
    while (scanf("%c", &symbol) != EOF) {
        if (symbol == '"') {
            printf("%s", (odd ? "``" : "''"));
            odd = !odd;
        }
        else {
            printf("%c", symbol);
        }
    }
    return 0;
}
