/* 11048
 * Automatic Correction of Misspellings
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORDS   10000
#define MAX_STRING  30

typedef struct {
    char string[MAX_STRING];
    int size;
} word_t;

word_t dict[MAX_WORDS], *sorted[MAX_WORDS];
int size;

/* Compare words */
int compare(const void *a, const void *b) {
    word_t *x = * (word_t **) a, *y = * (word_t **) b;
    return strcmp(x->string, y->string);
}

/* Whether a word corresponds to a dictionary entry */
int correspond(word_t *word, word_t *entry) {
    char *w, *e;
    if (abs(word->size - entry->size) > 1)
        return 0;
    for (w = word->string, e = entry->string; *w == *e && *w != 0; w++, e++)
        ;
    if (*w == 0 && *e == 0)
        return 1;
    if (word->size == entry->size + 1)
        return strcmp(w + 1, e) == 0 ? -1 : 0;
    if (word->size == entry->size - 1)
        return strcmp(w, e + 1) == 0 ? -1 : 0;
    if (*w == *(e + 1) && *e == *(w + 1))
        return strcmp(w + 2, e + 2) == 0 ? -1 : 0;
    return strcmp(w + 1, e + 1) == 0 ? -1 : 0;
}

/* Check which kind of entry a word is */
void print_which_kind(word_t *word) {
    int i, kind;
    word_t **pos = bsearch(&word, sorted, size, sizeof (word_t *), compare);
    printf("%s is ", word->string);
    if (pos != NULL) {
        printf("correct\n");
        return;
    }
    for (i = 0, kind = 0; kind == 0 && i < size; i++) {
        kind = correspond(word, &dict[i]);
        assert(kind <= 0);
        if (kind < 0)
            printf("a misspelling of %s\n", dict[i].string);
    }
    if (kind == 0)
        printf("unknown\n");
}

/* Main function */
int main() {
    int i, n;
    assert(scanf("%d", &size) != EOF);
    for (i = 0; i < size; i++) {
        assert(scanf(" %s", dict[i].string) != EOF);
        dict[i].size = strlen(dict[i].string);
        sorted[i] = &dict[i];
    }
    qsort(sorted, size, sizeof (word_t *), compare);
    assert(scanf("%d", &n) != EOF);
    for (i = 0; i < n; i++) {
        word_t word;
        assert(scanf(" %s", word.string) != EOF);
        word.size = strlen(word.string);
        print_which_kind(&word);
    }
    return EXIT_SUCCESS;
}
