/* 12592
 * Slogan Learning of Princess
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       20
#define MAX_STRING  150

typedef struct {
    char line[MAX_STRING], choir[MAX_STRING];
} chant_t;

chant_t chant[MAX_N], *dict[MAX_N];
int size;

/* Find or insert */
chant_t * find_insert(char *line, char *choir) {
    int start = 0, end = size;
    while (start < end) {
        int middle = (start + end) / 2;
        int cmp = strcmp(line, dict[middle]->line);
        if (cmp == 0)
            return dict[middle];
        else if (cmp < 0)
            end = middle;
        else
            start = middle + 1;
    }
    assert(choir != NULL);
    strcpy(chant[size].line, line);
    strcpy(chant[size].choir, choir);
    for (end = size; end > start; end--)
        dict[end] = dict[end - 1];
    dict[start] = &chant[size++];
    return dict[start];
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char input[MAX_STRING], choir[MAX_STRING];
    int n;
    assert(READ(input));
    for (n = atoi(input), size = 0; n > 0; n--) {
        assert(READ(input) && READ(choir));
        find_insert(input, choir);
    }
    assert(READ(input));
    for (n = atoi(input); n > 0; n--) {
        chant_t *c;
        assert(READ(input));
        c = find_insert(input, NULL);
        printf("%s", c->choir);
    }
    return EXIT_SUCCESS;
}
