/* 10503
 * The dominoes solitaire
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DOMINOES    14
#define MIN(x,y)        ((x) < (y) ? (x) : (y))
#define MAX(x,y)        ((x) > (y) ? (x) : (y))

typedef struct {
    int v1, v2, used;
} domino_t;

domino_t domino[MAX_DOMINOES];
int num_dominoes;

/* Compare dominoes */
int compare(const void *a, const void *b) {
    domino_t *x = (domino_t *) a, *y = (domino_t *) b;
    if (x->v1 == y->v1)
        return x->v2 - y->v2;
    return x->v1 - y->v1;
}

/* Find permutation */
int find(int start, int length, int end) {
    if (length <= 0)
        return start == end;
    else {
        domino_t *last = NULL;
        int i;
        for (i = 0, length--; i < num_dominoes; i++) {
            domino_t *d = &domino[i];
            if (!d->used && (d->v1 == start || d->v2 == start) &&
                    (last == NULL || d->v1 != last->v1 || 
                     d->v2 != last->v2)) {
                d->used = 1;
                if (find(d->v1 == start ? d->v2 : d->v1, length, end))
                    return 1;
                d->used = 0, last = d;
            }
        }
        return 0;
    }
}

/* Main function */
int main() {
    int length;
    while (scanf("%d", &length) != EOF && length > 0) {
        int i, start, end;
        assert(scanf("%d %*d %d %d %*d", &num_dominoes, &start, &end) 
                != EOF);
        for (i = 0; i < num_dominoes; i++) {
            int a, b;
            domino_t *d = &domino[i];
            assert(scanf("%d %d", &a, &b) != EOF);
            d->v1 = MIN(a, b), d->v2 = MAX(a, b), d->used = 0;
        }
        qsort(domino, num_dominoes, sizeof (domino_t), compare);
        printf("%s\n", find(start, length, end) ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
