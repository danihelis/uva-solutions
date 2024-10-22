/* 353
 * Pesky Palindromes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  100

/* Main function */
int main() {
    char string[MAX_STRING];
    while (scanf(" %[^\n]", string) != EOF) {
        if (string[0] != 0) {
            char *ini, *end;
            int num_palidromes = 0;
            for (ini = string; *ini != 0; ini++) {
                for (end = ini; *end != 0; end++) {
                    char *f, *b, palindrome = 1;
                    for (f = ini, b = end; palindrome && f < b; f++, b--) {
                        palindrome = (*f == *b);
                    }
                    if (palindrome) {
                        char sub[MAX_STRING];
                        int length = end - ini + 1;
                        strncpy(sub, ini, length);
                        sub[length] = 0;
                        if (strstr(ini + 1, sub) == NULL) {
                            num_palidromes++;
                        }
                    }
                }
            }
            printf("The string '%s' contains %d palindromes.\n", string, num_palidromes);
        }
    }
    return 0;
}
