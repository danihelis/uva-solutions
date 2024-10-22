/* 10978
 * Let's Play Magic!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define CARD_LEN    3
#define WORD_LEN    21
#define MAX_CARDS   52

/* Main function */
int main() {
    char sequence[MAX_CARDS][CARD_LEN], card[CARD_LEN], word[WORD_LEN];
    int index[MAX_CARDS];
    int num_cards, num_indices;
    while (scanf("%d", &num_cards) == 1 && num_cards > 0) {
        int i, j, last;
        for (i = 0, num_indices = num_cards; i < num_indices; i++) {
            index[i] = i;
        }
        for (i = last = 0; i < num_cards; i++) {
            assert(scanf(" %s %s", card, word) == 2);
            last = (last + strlen(word) + num_indices - 1) % num_indices;
            strcpy(sequence[index[last]], card);
            for (j = last, num_indices--; j < num_indices; j++) {
                index[j] = index[j + 1];
            }
            if (last >= num_indices) last = 0;
        }
        for (i = 0; i < num_cards; i++) {
            printf("%s%c", sequence[i], i < num_cards - 1 ? ' ' : '\n');
        }
    }    
    return EXIT_SUCCESS;
}
