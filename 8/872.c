/* 872
 * Ordering
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_VARS    26
#define MAX_STR     500

typedef struct var_s {
    struct var_s *preceed[MAX_STR];
    int num_preceed, used, present;
} var_t;

var_t var[NUM_VARS];
char sequence[NUM_VARS];

/* Generate all permutations that respect the constraints */
int permute(int pos, int n) {
    int index, total = 0;
    if (pos == n) {
        for (index = 0; index < n; index++)
            printf("%c%c", sequence[index], index < n - 1 ? ' ' : '\n');
        return 1;
    }
    for (index = 0; index < NUM_VARS; index++) {
        var_t *v = &var[index];
        if (v->used && !v->present) {
            int i, satisfied;
            for (i = 0, satisfied = 1; satisfied && i < v->num_preceed; i++)
                satisfied = v->preceed[i]->present;
            if (satisfied) {
                v->present = 1;
                sequence[pos] = 'A' + index;
                total += permute(pos + 1, n);
                v->present = 0;
            }
        }
    }
    return total;
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STR, stdin) != NULL)
#define VAR(x)      (var[(x) - 'A'])
int main() {
    char *token, line[MAX_STR];
    int num_tests;
    assert(READ(line));
    for (num_tests = atoi(line); num_tests > 0; num_tests--) {
        int i, n;
        for (i = 0; i < NUM_VARS; i++)
            var[i].num_preceed = var[i].used = var[i].present = 0;
        assert(READ(line) && line[0] == '\n');
        assert(READ(line));
        for (n = 0, token = strtok(line, " \n"); token != NULL; 
                n++, token = strtok(NULL, " \n"))
            VAR(token[0]).used = 1;
        assert(READ(line));
        for (token = strtok(line, " \n"); token != NULL; 
                token = strtok(NULL, " \n")) {
            char before, after;
            assert(sscanf(token, "%c<%c", &before, &after) == 2);
            VAR(after).preceed[VAR(after).num_preceed++] = &VAR(before);
        }
        if (permute(0, n) == 0)
            printf("NO\n");
        if (num_tests > 1)
            printf("\n");
    }
    return EXIT_SUCCESS;
}
