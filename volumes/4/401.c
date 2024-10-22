/* 401
 * Palindromes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  30

char CHANGEABLE[]   = "AEHIJLMOSTUVWXYZ12358";
char MIRROR[]       = "A3HILJMO2TUVWXY51SEZ8";

/* Main function */
int main() {
    char input[MAX_STRING];
    while (scanf(" %s", input) != EOF) {
        int palin, mirror, length = strlen(input);
        char *s, *e;
        for (s = input, e = input + length - 1, palin = 1; palin && s < e; s++, e--) {
            palin = (*s == *e);
        }
        for (s = input, e = input + length - 1, mirror = 1; mirror && s <= e; s++, e--) {
            char *idx = strchr(CHANGEABLE, *s);
            mirror = (idx != NULL) && (*e == MIRROR[idx - CHANGEABLE]);
        }
        printf("%s -- is %s.\n\n", input, 
                (palin ? (mirror ? "a mirrored palindrome" : "a regular palindrome") :
                         (mirror ? "a mirrored string" : "not a palindrome")));
    }
    return 0;
}
