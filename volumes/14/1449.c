/* 1449
 * Dominating Patterns
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PATTERN_LENGTH  72
#define MAX_PATTERNS        150
#define MAX_INPUT           1000002

typedef struct {
    char query[MAX_PATTERN_LENGTH];
    int matches;
} pattern_t;

pattern_t pattern[MAX_PATTERNS];
char input[MAX_INPUT];


/* Determine the number of matches of a pattern in the input */
int find(pattern_t *p) {
    int backtrack[MAX_PATTERN_LENGTH];
    int i, j;

    /* Create a table with values for backtracking */
    i = 0, j = -1;
    backtrack[i] = j;
    while (p->query[i] != 0) {
        while (j >= 0 && p->query[i] != p->query[j]) {
            j = backtrack[j];
        }
        i++, j++;
        backtrack[i] = j;
    }

    /* Look for query in input */
    i = 0, j = 0, p->matches = 0;
    while (input[i] != 0) {
        while (j >= 0 && input[i] != p->query[j]) {
            j = backtrack[j];
        }
        i++, j++;
        if (p->query[j] == 0) {
            p->matches++;
            j = backtrack[j];
        }
    }
    return p->matches;
}


/* Main function */
int main() {
    int i, most, num_patterns;
    while (scanf("%d", &num_patterns) != EOF && num_patterns > 0) {
        for (i = 0; i < num_patterns; i++) {
            assert(scanf(" %s", pattern[i].query) != EOF);
        }
        assert(scanf(" %[^\n]", input) != EOF);
        for (i = 0, most = 0; i < num_patterns; i++) {
            pattern_t *p = &pattern[i];
            if (find(p) > most) most = p->matches;
        }
        printf("%d\n", most);
        for (i = 0; i < num_patterns; i++) {
            pattern_t *p = &pattern[i];
            if (p->matches == most) printf("%s\n", p->query);
        }
    }   
    return EXIT_SUCCESS;
}
