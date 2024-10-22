/* 719
 * Glass Beads
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BEADS   10000
#define MAX_STRING  (MAX_BEADS + 2)

typedef struct {
    int index, rank, fullrank;
} bead_t, *bead_p;

bead_t bead[MAX_BEADS];
char string[MAX_STRING];
int num_beads;

/* Compare two bids by fullrank */
int compare_bead(const void *a, const void *b) {
    bead_p x = *((bead_p *) a), y = *((bead_p *) b);
    return (x->fullrank != y->fullrank ? x->fullrank - y->fullrank : x->index - y->index);
}

/* Compute the suffix array from string and return the first element */
int compute_suffix_array() {
    bead_p sorted[MAX_BEADS];
    int k, s;
    for (k = 0; k < num_beads; k++) {
        bead[k].index = k;
        bead[k].fullrank = string[k];
        sorted[k] = &bead[k];
    }
    qsort(sorted, num_beads, sizeof (bead_p), compare_bead);
    for (s = 1; s < num_beads; s <<= 1) {
        sorted[0]->rank = 0;
        for (k = 1; k < num_beads; k++) {
            sorted[k]->rank = sorted[k - 1]->rank + 
                (sorted[k]->fullrank == sorted[k - 1]->fullrank ? 0 : 1);
        }
        for (k = 0; k < num_beads; k++) {
            int next = (sorted[k]->index + s) % num_beads;
            sorted[k]->fullrank = sorted[k]->rank * num_beads + bead[next].rank;
        }
        qsort(sorted, num_beads, sizeof (bead_p), compare_bead);
    }
    return sorted[0]->index;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf(" %s", string) != EOF);
        num_beads = strlen(string);
        printf("%d\n", compute_suffix_array() + 1);
    }
    return 0;
}
