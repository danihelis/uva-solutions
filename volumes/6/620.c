/* 620
 * Cellular Structure
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING      10000

#define SIMPLE          1
#define FULLY_GROWN     2
#define MUTANT          3
#define MUTAGENIC       4


/* Check recursively a chain to give it a proper form label */
int get_form(char *chain, int length) {
    int value = MUTANT;
    if (length == 1 && chain[0] == 'A') return SIMPLE;
    if (length <= 2) return MUTANT;

    if (chain[length - 2] == 'A' && chain[length - 1] == 'B') {
        value = get_form(chain, length - 2);
        if (value != MUTANT) value = FULLY_GROWN;
    } else if (chain[0] == 'B' && chain[length - 1] == 'A') {
        value = get_form(chain + 1, length - 2);
        if (value != MUTANT) value = MUTAGENIC;
    }
    return value;
}

/* Main function */
int main() {
    int num_tests;
    char line[MAX_STRING];

    assert(fgets(line, MAX_STRING, stdin) != NULL);
    assert(sscanf(line, "%d", &num_tests) == 1);

    while (num_tests-- > 0) {
        int length, form;

        assert(fgets(line, MAX_STRING, stdin) != NULL);
        length = strlen(line);
        assert(length < MAX_STRING);

        form = get_form(line, length - 1);
        printf("%s\n", form == SIMPLE ? "SIMPLE" : form == FULLY_GROWN ?
                "FULLY-GROWN" : form == MUTANT ? "MUTANT" : "MUTAGENIC");
    }
    return EXIT_SUCCESS;
}
