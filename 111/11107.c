/* 11107
 * Life Forms
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DNAS    100
#define MAX_STRING  1010
#define MAX_CHARS  (MAX_DNAS * MAX_STRING)

typedef char string_t[MAX_STRING];

typedef struct {
    char *content;
    long rank, fullrank;
    int dna, index, lcp;
} char_t, *char_p;

string_t dna[MAX_DNAS];
char_t letter[MAX_CHARS], *letter_ptr[MAX_CHARS];
char_p best[MAX_STRING];
int num_dnas, num_best, best_length;
long num_letters, max_letters;

/* Compares two letters by fullrank */
int compare(const void *a, const void *b) {
    char_p x = *((char_p *) a), y = *((char_p *) b);
    return (x->fullrank < y->fullrank ? -1 : x->fullrank == y->fullrank ? 0 : 1);
}

/* Print suffix array */
void print_suffix_array() {
    int i;
    fprintf(stderr, "DNAS = %d, LETTERS = %ld, MAX_LETTER = %ld\n", num_dnas,
            num_letters, max_letters);
    for (i = 0; i < num_letters; i++) {
        char_p p = letter_ptr[i];
        fprintf(stderr, "%d. DNA = %d | I = %d | R = %ld | FR = %ld | LCP = %d | CONTENT = '%s'\n", 
                i, p->dna, p->index, p->rank, p->fullrank, p->lcp, p->content);
    }
    fflush(stderr);
}

/* Create suffix array  */
void create_suffix_array() {
    int i, d, n;
    char *c;
    char_p p, q;
    for (d = 0, i = 0; d < num_dnas; d++, i++) {
        for (c = dna[d]; *c != 0; i++, c++) {
            char_p p = &letter[i];
            p->content = c;
            p->dna = d;
            p->index = i;
            p->fullrank = *c;
            letter_ptr[i] = p;
        }
        p = &letter[i];
        p->content = c;
        p->dna = d;
        p->index = i;
        p->fullrank = 0;
        letter_ptr[i] = p;
    }
    
    assert(i == num_letters);
    qsort(letter_ptr, num_letters, sizeof (char_p), compare);
    
    for (d = 1; d <= max_letters; d *= 2) {
        letter_ptr[0]->rank = 0;
        for (i = 1; i < num_letters; i++) {
            p = letter_ptr[i], q = letter_ptr[i - 1];
            p->rank = q->rank + (p->fullrank == q->fullrank ? 0 : 1);
        }
        for (i = 0; i < num_letters; i++) {
            p = letter_ptr[i];
            n = p->index + d;
            p->fullrank = p->rank * num_letters + (n < num_letters ? letter[n].rank : 0);
        }
        for (i = 0, n = 1; n < num_letters; n++) {
            if (letter_ptr[n]->rank != letter_ptr[i]->rank) {
                qsort(letter_ptr + i, n - i, sizeof (char_p), compare);
                i = n;
            }
        }
        qsort(letter_ptr + i, n - i, sizeof (char_p), compare);
    }
}

/* Create LCP array */
void create_lcp_array() {
    int i, equal;
    char_p p, q;
    char *r, *s;
    for (i = 0; i < num_letters; i++) {
        letter_ptr[i]->rank = i;
    }
    for (i = 0, equal = 0; i < num_letters; i++) {
        p = &letter[i];
        if (p->rank < num_letters - 1) {
            q = letter_ptr[p->rank + 1];
            for (r = p->content + equal, s = q->content + equal; 
                    *r != 0 && *s != 0 && *r == *s; equal++, r++, s++)
                ;
            p->lcp = equal;
            equal = (equal > 0 ? equal - 1 : 0);
        }
    }
}

/* Determine best prefixes */
void determine_best_prefixes() {
    int count[MAX_DNAS], non_zero, start, end, i, half, min;
    memset(count, 0, num_dnas * sizeof (int));
    half = num_dnas / 2, start = num_dnas, end = num_dnas, non_zero = 0;
    num_best = 0, best_length = 0;
    while (start < num_letters) {
        while (end < num_letters && non_zero <= half) {
            if (count[letter_ptr[end]->dna]++ == 0) {
                non_zero++;
            }
            end++;
        }
        if (non_zero <= half) {
            break;
        }
        for (i = start, min = max_letters; min >= best_length && i < end - 1; i++) {
            char_p p = letter_ptr[i];
            if (p->lcp < min) {
                min = p->lcp;
            }
        }
        if (min > 0 && min >= best_length) {
            if (min > best_length) {
                num_best = 0, best_length = min;
            }
            for (i = start; i < end - 1; i++) {
                char_p p = letter_ptr[i];
                if (p->lcp == best_length && (num_best == 0 || 
                            strncmp(best[num_best - 1]->content, p->content, best_length) != 0)) {
                    best[num_best++] = p;
                }
            }
        }
        if (--count[letter_ptr[start++]->dna] == 0) {
            non_zero--;
        }
    }
}

/* Print best prefixes */
void print_best_prefixes() {
    if (num_best == 0 || best_length == 0) {
        printf("?\n");
    }
    else {
        int i, k;
        for (i = 0; i < num_best; i++) {
            char *c;
            for (k = 0, c = best[i]->content; k < best_length; k++, c++) {
                printf("%c", *c);
            }
            printf("\n");
        }
    }
}

/* Main function */
int main() {
    char first = 1;
    while (scanf("%d", &num_dnas) != EOF && num_dnas > 0) {
        int i, s;
        (first ? (void) (first = 0) : (void) printf("\n"));
        for (i = 0, max_letters = 0, num_letters = 0; i < num_dnas; i++) {
            assert(scanf(" %s", dna[i]) != EOF);
            s = strlen(dna[i]);
            num_letters += s + 1;
            if (s > max_letters) {
                max_letters = s;
            }
        }
        if (i == 1) {
            printf("%s\n", dna[0]);
            continue;
        }
        create_suffix_array();
        create_lcp_array();
        determine_best_prefixes();
        print_best_prefixes();
#if 0
        print_suffix_array();
#endif
    }
    return 0;
}
