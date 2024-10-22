/* 11283
 * Playing Boggle
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORDS   100
#define MAX_STRING  20
#define NUM_DIM     4
#define NUM_DIR     8
#define INSIDE(x)   ((x) >= 0 && (x) < NUM_DIM)

typedef struct {
    char word[MAX_STRING];
    int used, size;
} word_t;

word_t word[MAX_WORDS], *dict[MAX_WORDS];
int num_words, points;
char grid[NUM_DIM][NUM_DIM + 2], used[NUM_DIM][NUM_DIM], pattern[MAX_STRING];
int drow[NUM_DIR] = {-1, -1, 0, 1, 1, 1, 0, -1},
    dcol[NUM_DIR] = {0, 1, 1, 1, 0, -1, -1, -1};

/* Compare two words, for sorting */
int compare(const void *a, const void *b) {
    word_t *x = * (word_t **) a, *y = * (word_t **) b;
    return strcmp(x->word, y->word);
}

/* Binary search for N characters */
word_t * search(char *key, int n) {
    int start = 0, end = num_words;
    while (start < end) {
        int middle = (start + end) / 2;
        int comp = strncmp(dict[middle]->word, key, n);
        if (comp == 0)
            return dict[middle];
        else if (comp < 0)
            start = middle + 1;
        else
            end = middle;
    }
    return NULL;
}

/* Find word pattern and compute points */
void find_patterns(int i, int j, int n) {
    word_t *match;
    int k;
    pattern[n++] = grid[i][j];
    match = search(pattern, n);
    if (match == NULL) {
        return;
    }
    pattern[n] = 0;
    match = search(pattern, MAX_STRING);
    if (match != NULL && !match->used) {
        match->used = 1;
        points += n == 3 ? 1 : n >= 8 ? 11 : n == 7 ? 5 : n - 3;
    }
    used[i][j] = 1;
    for (k = 0; k < NUM_DIR; k++) {
        int ni = i + drow[k], nj = j + dcol[k];
        if (INSIDE(ni) && INSIDE(nj) && !used[ni][nj])
            find_patterns(ni, nj, n);
    }
    used[i][j] = 0;
}

/* Main function */
int main() {
    int test, num_tests, i, j;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        for (i = 0; i < NUM_DIM; i++)
            assert(scanf(" %s", grid[i]) != EOF);
        assert(scanf("%d", &num_words) != EOF);
        for (i = 0; i < num_words; i++) {
            word_t *w = &word[i];
            assert(scanf(" %s", w->word) != EOF);
            w->used = 0, w->size = strlen(w->word);
            dict[i] = w;
        }
        qsort(dict, num_words, sizeof (word_t *), compare);
        memset(used, 0, NUM_DIM * NUM_DIM);
        for (i = 0, points = 0; i < NUM_DIM; i++)
            for (j = 0; j < NUM_DIM; j++)
                find_patterns(i, j, 0);
        printf("Score for Boggle game #%d: %d\n", test, points);
    }
    return EXIT_SUCCESS;
}
