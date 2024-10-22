/* 458
 * The Decoder
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define CODE    ('1' - '*')

/* Main function */
int main() {
    char symbol;
    while (scanf("%c", &symbol) != EOF) {
        printf("%c", (symbol == '\n' ? '\n' : symbol - CODE));
    }
    return 0;
}
