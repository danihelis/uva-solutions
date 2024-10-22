/* 10222
 * Decode the Mad man
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

char code[] = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";
char caps[] = "~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?";

/* Main function */
int main() {
    char symbol, *which;
    while (scanf("%c", &symbol) != EOF) {
        which = strchr(code, symbol);
        if (which == NULL) {
            which = strchr(caps, symbol);
            if (which != NULL) {
                which = code + (which - caps);
            }
        }
        printf("%c", which != NULL && which > code + 1 ? *(which - 2) : symbol);
    }
    return 0;
}
