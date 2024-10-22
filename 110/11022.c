/* 11022
 * String Factoring
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    80
#define MAX_STRING  (MAX_SIZE + 2)

int compute_factoring(char *s, int length);

/* Compute patterns starting from a string position */
int compute_patterns(char *s, int index, int length, int factor[]) {
    char *t, *i, *j;
    int best = 1 + factor[index + 1];
    for (t = s + 1; (t - s) * 2 <= length - index; t++) {
        j = t;
        do {
            for (i = s; i != t && *i == *j; i++, j++)
                ;
            if (i == t) {
                int value = compute_factoring(s, t - s) + 
                    factor[index + j - s];
                if (value < best)
                    best = value;
            }
        } while (i == t);
    }
    return best;
}

/* Compute all patterns from the string's suffixes */
int compute_factoring(char *s, int length) {
    char string[MAX_STRING];
    int index, patterns[MAX_SIZE];
    if (length <= 1)
        return 1;
    strncpy(string, s, length);
    string[length] = 0;
    patterns[length] = 0;
    for (index = length - 1; index >= 0; index--)
        patterns[index] = compute_patterns(string + index, index, length,
                patterns);
    return patterns[0];
}

/* Main function */
int main() {
    char input[MAX_STRING];
    while (scanf(" %s", input) != EOF && input[0] != '*')
        printf("%d\n", compute_factoring(input, strlen(input)));
    return EXIT_SUCCESS;
}
