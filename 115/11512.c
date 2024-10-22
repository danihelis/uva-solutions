/* 11512
 * GATTACA
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1010

typedef struct {
    int rank, fullrank, index, lcp;
} suffix_t, *suffix_p;

suffix_t suffix[MAX_STRING];
suffix_p suffix_ptr[MAX_STRING];
int num_suffixes;
suffix_p best;
int best_length, repetitions;

/* Compare two suffixes by fullrank */
int compare_rank(const void *a, const void *b) {
    suffix_p x = *((suffix_p *) a), y = *((suffix_p *) b);
    return x->fullrank - y->fullrank;
}

/* Print suffix array */
void print_suffix_array(char *string) {
    int i;
    fprintf(stderr, "NUM_SUFFIXES = %d | STRING: '%s'\n", num_suffixes, string);
    for (i = 0; i < num_suffixes; i++) {
        suffix_p p = suffix_ptr[i];
        fprintf(stderr, "%d. IDX = %d | R = %d | FR = %d | LCP = %d | C = '%s'\n", i,
                p->index, p->rank, p->fullrank, p->lcp, string + p->index);
        fflush(stderr);
    }
}

/* Compute suffix array */
#define SET_SUFFIX(i, s)    do { \
        suffix_p _p = &suffix[i]; \
        _p->fullrank = *s; \
        _p->index = i; \
        suffix_ptr[i] = _p; \
    } while (0)
void compute_suffix_array(char *string) {
    int i, s;
    for (i = 0; *string != 0; i++, string++) {
        SET_SUFFIX(i, string);
    }
    SET_SUFFIX(i, string);
    num_suffixes = i + 1;
    qsort(suffix_ptr, num_suffixes, sizeof (suffix_p), compare_rank);
    for (s = 1; s < num_suffixes; s *= 2) {
        suffix_ptr[0]->rank = 0;
        for (i = 1; i < num_suffixes; i++) {
            suffix_p p = suffix_ptr[i], q = suffix_ptr[i - 1];
            p->rank = q->rank + (p->fullrank == q->fullrank ? 0 : 1);
        }
        for (i = 0; i < num_suffixes; i++) {
            suffix_p p = suffix_ptr[i];
            int k = p->index + s;
            p->fullrank = p->rank * num_suffixes + (k < num_suffixes ? suffix[k].rank : 0);
        }
        qsort(suffix_ptr, num_suffixes, sizeof (suffix_p), compare_rank);
    }
}

/* Compute longest common prefix array */
void compute_lcp_array(char *string) {
    int i, equal;
    char *r, *s;
    for (i = 0; i < num_suffixes; i++) {
        suffix_ptr[i]->rank = i;
    }
    for (i = 0, equal = 0; i < num_suffixes - 1; i++) {
        if (suffix[i].rank < num_suffixes - 1) {
            suffix_p p = &suffix[i], q = suffix_ptr[suffix[i].rank + 1];
            for (r = string + p->index + equal, s = string + q->index + equal;
                    *r != 0 && *s != 0 && *r == *s; equal++, r++, s++)
                ;
            p->lcp = equal;
            equal = (equal > 0 ? equal - 1 : 0);
        }
    }
}

/* Compute longest repeated prefix */
void compute_longest_repeated(char *string) {
    int i, can_be_equal;
    best_length = 0, repetitions = 0, best = NULL, can_be_equal = 0;
    for (i = 1; i < num_suffixes - 1; i++) {
        suffix_p p = suffix_ptr[i];
        if (p->lcp > best_length) {
            best_length = p->lcp;
            best = p;
            repetitions = 1;
            can_be_equal = 1;
        }
        else if (can_be_equal && p->lcp == best_length) {
            can_be_equal = strncmp(string + p->index, string + best->index, best_length) == 0;
            repetitions += (can_be_equal ? 1 : 0);
        }
    }
}

/* Main function */
int main() {
    int num_tests;
    char string[MAX_STRING];
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf(" %s", string) != EOF);
        compute_suffix_array(string);
        compute_lcp_array(string);
        compute_longest_repeated(string);
#if 0
        print_suffix_array(string);
#endif
        if (best_length == 0) {
            printf("No repetitions found!\n");
        }
        else {
            int i;
            char *c;
            for (i = 0, c = string + best->index; i < best_length; i++, c++) {
                printf("%c", *c);
            }
            printf(" %d\n", repetitions + 1);
        }
    }
    return 0;
}
