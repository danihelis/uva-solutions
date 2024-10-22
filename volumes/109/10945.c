/* 10945
 * Mother bear
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1000000

/* Main function */
int main() {
    char input[MAX_STRING], alpha[MAX_STRING];
    while (fgets(input, MAX_STRING, stdin) != NULL && strcmp(input, "DONE\n") != 0) {
        char *c, *a, palin;
        for (c = input, a = alpha; *c != '\n'; c++) {
            if (isalpha(*c)) {
                *a = tolower(*c);
                a++;
            }
        }
        for (palin = 1, c = alpha, a--; palin && c < a; c++, a--) {
            palin = *c == *a;
        }
        printf("%s\n", palin ? "You won't be eaten!" : "Uh oh..");
    }
    return 0;
}
