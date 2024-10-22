/* 10008
 * What's Cryptanalysis?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CHARS   28

typedef struct {
    int count;
    char index;
} char_t, *char_p;

char_t letter[MAX_CHARS];

/* Compare two letters */
int compare(const void *a, const void *b) {
    char_p x = (char_p) a, y = (char_p) b;
    return (x->count == y->count ? x->index - y->index : y->count - x->count);
}

/* Main function */
int main() {
    int i;
    char symbol;
    for (i = 0; i < MAX_CHARS; i++) {
        letter[i].count = 0, letter[i].index = i;
    }

    while (scanf("%c", &symbol) != EOF && symbol != '\n')
        ;
    while (scanf("%c", &symbol) != EOF) {
        if (isalpha(symbol)) {
            i = tolower(symbol) - 'a';
            letter[i].count++;
        }
    }
    
    qsort(letter, MAX_CHARS, sizeof (char_t), compare);
    for (i = 0; i < MAX_CHARS && letter[i].count > 0; i++) {
        printf("%c %d\n", letter[i].index + 'A', letter[i].count);
    }
    return 0;
}
