/* 10082
 * WERTYU
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
    char input[] = "1234567890-=WERTYUIOP[]\\SDFGHJKL;'XCVBNM,./";
    char code[]  = "`1234567890-QWERTYUIOP[]ASDFGHJKL;ZXCVBNM,.";
    char symbol;
    while (scanf("%c", &symbol) != EOF) {
        char *index = strchr(input, symbol);
        printf("%c", (index == NULL ? symbol : code[index - input]));
    }
    return 0;
}
