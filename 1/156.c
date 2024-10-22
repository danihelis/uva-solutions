/* 156
 * Ananagrams
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  22
#define MAX_WORDS   1000

typedef struct {
    char entry[MAX_STRING];
    char sorted[MAX_STRING];
    int size, ananagram;
} word_t, *word_p;

word_t dict[MAX_WORDS], *p_dict[MAX_WORDS];
int n;

/* Compare chars */
int compare_chars(const void *a, const void *b) {
    return *((char *) a) - *((char *) b);
}

/* Compare words */
int compare_words(const void *a, const void *b) {
    word_p wa = *((word_p *) a), wb = *((word_p *) b);
    return (wa->ananagram && wb->ananagram) ? strcmp(wa->entry, wb->entry) : 
        (wb->ananagram - wa->ananagram);
}

/* Main function */
int main() {
    char input[MAX_STRING];
    int i, j;

    n = 0;
    while (scanf("%s ", input) != EOF && input[0] != '#') {
        char *c, *e, *s;
        word_p w = &dict[n];
        p_dict[n++] = w;
        for (c = input, e = w->entry, s = w->sorted, w->size = 0, w->ananagram = 1; 
                *c != 0; c++, e++, s++, w->size++) {
            *e = *c, *s = tolower(*c);
        }
        *e = 0, *s = 0;
        qsort(w->sorted, w->size, sizeof (char), compare_chars);
    }
    
    for (i = 0; i < n; i++) {
        word_p y, x = &dict[i];
        for (j = i + 1; j < n; j++) {
            y = &dict[j];
            if (x->size == y->size && strcmp(x->sorted, y->sorted) == 0) {
                x->ananagram = 0, y->ananagram = 0;
            }
        }
    }
    qsort(p_dict, n, sizeof (word_p), compare_words);
    for (i = 0; i < n && p_dict[i]->ananagram; i++) {
        printf("%s\n", p_dict[i]->entry);
    }
    return 0;
}
