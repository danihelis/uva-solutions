/* 10260
 * Soundex
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

char code[] =   "BFPVCGJKQSXZDTLMNR";
char value[] =  "111122222222334556";

/* Main function */
int main() {
    char letter, *p, val, last = 0;
    while (scanf("%c", &letter) != EOF) {
        p = strchr(code, letter);
        if (p == NULL) {
            last = 0;
            (letter == '\n' ? printf("\n") : 0);
        }
        else if ((val = value[p - code]) != last) {
            printf("%c", val);
            last = val;
        }
    }
    return 0;
}
