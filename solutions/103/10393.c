/* 10393
 * The One-Handed Typist
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_WORDS   1000
#define MAX_STRING  55
#define MAX_SET     7
#define NUM_FINGERS 10

char handcap[NUM_FINGERS][MAX_SET] = {
    "qaz",
    "wsx",
    "edc",
    "rfvtgb",
    " ",
    " ",
    "yhnujm",
    "ik,",
    "ol.",
    "p;/"
};

int blocked[NUM_FINGERS];
char dict[MAX_WORDS][MAX_STRING], *sorted[MAX_WORDS];
int size, fingers;

/* Compare words */
int compare(const void *a, const void *b) {
    return strcmp(* (char **) a, * (char **) b);
}

/* Main function */
int main() {
    while (scanf("%d %d", &fingers, &size) != EOF) {
        int i, j, best_size, count;
        char *biggest[MAX_WORDS];
        for (i = 0; i < fingers; i++) {
            assert(scanf("%d", &blocked[i]) != EOF);
            blocked[i]--;
        }
        for (i = 0; i < size; i++) {
            assert(scanf(" %s", dict[i]) != EOF);
            sorted[i] = dict[i];
        }
        qsort(sorted, size, sizeof (char *), compare);
        for (i = best_size = count = 0; i < size; i++) {
            int word_size = strlen(sorted[i]);
            if (word_size >= best_size) {
                int possible = i == 0 || 
                        strcmp(sorted[i], sorted[i - 1]) != 0;
                char *word = sorted[i];
                for (j = 0; possible && j < fingers; j++)
                    possible = strpbrk(word, handcap[blocked[j]]) == NULL;
                if (possible) {
                    if (word_size > best_size)
                        count = 0, best_size = word_size;
                    biggest[count++] = word;
                }
            }
        }
        printf("%d\n", count);
        for (i = 0; i < count; i++)
            printf("%s\n", biggest[i]);
    }
    return EXIT_SUCCESS;
}
