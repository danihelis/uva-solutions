/* 499
 * What's The Frequency, Kenneth?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_ALPHABET    26
#define MAX_LETTERS     (2 * MAX_ALPHABET)

typedef struct {
    int count, index;
} letter_t, *letter_p;

letter_t letter[MAX_LETTERS];

/* Compare */
int compare(const void *a, const void *b) {
    letter_p x = (letter_p) a, y = (letter_p) b;
    return (x->count == y->count ? x->index - y->index : y->count - x->count);
}

/* Main function */
#define ZERO_COUNT()    do { \
                            int _i; \
                            for (_i = 0; _i < MAX_LETTERS; _i++) \
                                letter[_i].index = _i, letter[_i].count = 0; \
                        } while (0)
int main() {
    char symbol;
    ZERO_COUNT();
    while (scanf("%c", &symbol) != EOF) {
        if (symbol == '\n') {
            int i, c;
            qsort(letter, MAX_LETTERS, sizeof (letter_t), compare);
            for (i = 0, c = letter[0].count; i < MAX_LETTERS && letter[i].count == c; i++) {
                printf("%c", letter[i].index + (letter[i].index < MAX_ALPHABET ? 'A' : 
                            'a' - MAX_ALPHABET));
            }
            printf(" %d\n", c);
            ZERO_COUNT();
        }
        else if (isalpha(symbol)) {
            letter[symbol - (isupper(symbol) ? 'A' : 'a' - MAX_ALPHABET)].count++;
        }
    }
    return 0;
}
