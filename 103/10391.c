/* 10391
 * Compound Words
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  200
#define MAX_WORDS   120000

typedef char string_t[MAX_STRING];

string_t word[MAX_WORDS];
char *result[MAX_WORDS];
char used[MAX_WORDS];
int num_words, num_resuts;

/* Compare strings */
int compare(const void *a, const void *b) {
    return strcmp(*((char **) a), *((char **) b));
}

/* Find all words that form composition with the current word */
void find_composition(int i) {
    int j;
    for (j = i + 1; j < num_words; j++) {
        char *w, *c, equals;
        for (w = word[i], c = word[j], equals = 1; 
                equals && *w != '\n' && *c != '\n'; w++, c++) {
            equals = (*w == *c);
        }
        if (!equals || *w != '\n') {
            break;
        }
        if (!used[j] && bsearch(c, word, num_words, sizeof (string_t), 
                    (int (*) (const void *, const void *)) strcmp) != NULL) {
            result[num_resuts++] = word[j];
            used[j] = 1;
        }
    }
}

/* Main function */
int main() {
    int i;
    num_words = 0, num_resuts = 0;
    while (fgets(word[num_words], MAX_STRING, stdin) != NULL) {
        assert(strlen(word[num_words]) < MAX_STRING);
        num_words++;
    }
    memset(used, 0, num_words);
    for (i = 0; i < num_words - 1; i++) {
        find_composition(i);
    }
    qsort(result, num_resuts, sizeof (char *), compare);
    for (i = 0; i < num_resuts; i++) {
        printf("%s", result[i]);
    }
    return 0;
}
