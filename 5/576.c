/* 576
 * Haiku Review
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  300
#define NUM_LINES   3
#define END_INPUT   "e/o/i"

const int expected[NUM_LINES] = {5, 7, 5};
const char vowels[] = "aeiouy";

/* Main function */
int main() {
    char input[MAX_STRING];
    while (scanf(" %[^\n]", input) != EOF && strcmp(input, END_INPUT) != 0) {
        int line, syllables, error;
        char *p, syl;
        for (line = 0, syllables = 0, syl = 0, p = input, error = 0; !error && *p != 0; p++) {
            if (*p == '/') {
                error = syllables != expected[line++];
                syl = 0, syllables = 0;
            }
            else if (strchr(vowels, *p) != NULL) {
                syllables += syl ? 0 : 1;
                syl = 1;
            }
            else {
                syl = 0;
            }
        }
        if (!error) {
            error = syllables != expected[line++];
        }
        printf("%c\n", error ? line + '0' : 'Y');
    }
    return 0;
}
