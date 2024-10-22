/* 11577
 * Letter Frequency
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  210
#define NUM_CHARS   26

typedef struct {
    char letter;
    int count;
} char_t;

char_t freq[NUM_CHARS];

/* Compare two char_t */
int compare(const void *a, const void *b) {
    char_t *x = (char_t *) a, *y = (char_t *) b;
    return x->count == y->count ? x->letter - y->letter : 
            y->count - x->count;
}

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    int num_tests;
    char input[MAX_STRING], *c;
    assert(READ(input));
    for (num_tests = atoi(input); num_tests > 0; num_tests--) {
        int i;
        assert(READ(input));
        for (i = 0; i < NUM_CHARS; i++)
            freq[i].letter = 'a' + i, freq[i].count = 0;
        for (c = input; *c != 0; c++)
            if (isalpha(*c))
                freq[tolower(*c) - 'a'].count++;
        qsort(freq, NUM_CHARS, sizeof (char_t), compare);
        for (i = 0; i < NUM_CHARS && freq[i].count == freq[0].count; i++)
            printf("%c", freq[i].letter);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
