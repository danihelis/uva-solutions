/* 454
 * Anagrams
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1000
#define MAX_WORDS   100

typedef struct {
    char entry[MAX_STRING], sorted[MAX_STRING];
    int size;
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
    return strcmp(wa->entry, wb->entry);
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    int i, j, num_tests;
    char input[MAX_STRING];
    assert(READ(input));
    num_tests = atoi(input);
    assert(READ(input));
    for (; num_tests > 0; num_tests--) {
        n = 0;
        while (READ(input) && input[0] != '\n') {
            char *e, *s, *c;
            word_p w = &dict[n];
            p_dict[n++] = w;
            for (c = input, e = w->entry, s = w->sorted, w->size = 0; *c != '\n'; c++, e++) {
                *e = *c;
                if (!isspace(*c)) {
                    *s = *c;
                    s++, w->size++;
                }
            }
            *e = 0, *s = 0;
            qsort(w->sorted, w->size, sizeof (char), compare_chars);
        }
        qsort(p_dict, n, sizeof (word_p), compare_words);
        for (i = 0; i < n; i++) {
            word_p wi = p_dict[i];
            for (j = i + 1; j < n; j++) {
                word_p wj = p_dict[j];
                if (wi->size == wj->size && strcmp(wi->sorted, wj->sorted) == 0) {
                    printf("%s = %s\n", wi->entry, wj->entry);
                }
            }
        }
        (num_tests > 1 ? printf("\n") : 0);
    }
    return 0;
}
