/* 1584
 * Circular Sequence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  300

/* Main function */
int main() {
    char input[MAX_STRING], dna[MAX_STRING], *min;
    assert(scanf("%*d") != EOF);
    while (scanf(" %s", input) == 1) {
        int i, len = strlen(input);
        strcpy(dna, input);
        strcpy(dna + len, input);
        for (min = dna, i = 1; i < len; i++)
            if (strcmp(dna + i, min) < 0)
                min = dna + i;
        strncpy(input, min, len);
        printf("%s\n", input);
    }
    return EXIT_SUCCESS;
}
