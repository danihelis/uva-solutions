/* 10282
 * Babelfish
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORDS   100000
#define MAX_STRING  12
#define MAX_LINE    (3 * MAX_STRING)
#define READ(x, s)  (fgets(x, s, stdin) != NULL)

typedef struct {
    char key[MAX_STRING], value[MAX_STRING];
} word_t;

word_t word[MAX_WORDS], *dict[MAX_WORDS];
int size;

/* Compare two words */
int compare(const void *a, const void *b) {
    return strcmp((* (word_t **) a)->key, (* (word_t **) b)->key);
}

/* Main function */
int main() {
    char line[MAX_LINE];
    word_t ref, *ref_p, **find;
    size = 0;
    while (READ(line, MAX_LINE) && line[0] != '\n') {
        word_t *w = &word[size];
        strcpy(w->value, strtok(line, " "));
        strcpy(w->key, strtok(NULL, " "));
        dict[size++] = w;
    }
    qsort(dict, size, sizeof (word_t *), compare);
    ref_p = &ref;
    while (READ(ref.key, MAX_STRING)) {
        find = bsearch(&ref_p, dict, size, sizeof (word_t *), compare);
        if (find != NULL)
            printf("%s\n", (*find)->value);
        else
            printf("eh\n");
    }
    return EXIT_SUCCESS;
}
