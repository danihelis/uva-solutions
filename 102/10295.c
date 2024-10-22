/* 10295
 * Hay Points
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  200
#define MAX_N       1000

typedef struct {
    char word[MAX_STRING];
    int cost;
} entry_t;

/* Compare entries */
int compare(const void *a, const void *b) {
    entry_t *x = * (entry_t **) a, *y = * (entry_t **) b;
    return strcmp(x->word, y->word);
}

/* Main function */
int main() {
    entry_t entry[MAX_N], *dict[MAX_N], unit, *key, **found;
    int i, size, tests, total_cost;
    assert(scanf("%d %d", &size, &tests) == 2);
    for (i = 0; i < size; i++) {
        entry_t *e = &entry[i];
        assert(scanf(" %s %d", e->word, &e->cost) == 2);
        dict[i] = e;
    }
    qsort(dict, size, sizeof (entry_t *), compare);
    key = &unit;
    for (; tests > 0; tests--) {
        total_cost = 0;
        while (scanf(" %s", unit.word) != EOF && unit.word[0] != '.') {
            found = bsearch(&key, dict, size, sizeof (entry_t *), compare);
            if (found != NULL)
                total_cost += (*found)->cost;
        }
        printf("%d\n", total_cost);
    }
    return EXIT_SUCCESS;
}
