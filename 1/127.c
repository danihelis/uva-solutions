/* 127
 * "Accordian" Patience
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CARDS 52

typedef char card_t[3];
typedef struct {
    card_t card[MAX_CARDS];
    int top;
} pile_t;

pile_t pile[MAX_CARDS];
int num_piles;

#define PUSH(i, c) strcpy(pile[i].card[pile[i].top++], c)
#define NEW_PUSH(c) PUSH(num_piles, c); num_piles++
#define POP(i) pile[i].card[--pile[i].top]
#define EMPTY(i) (pile[i].top == 0)
#define TOP(i) pile[i].card[pile[i].top - 1]
#define MATCH(i, j) (TOP(i)[0] == TOP(j)[0] || TOP(i)[1] == TOP(j)[1])

/* Try to replace cards following the rules of patience */
void replace(int start) {
    static int diff[2] = {-3, -1};
    int i, match, place;
    for (match = -1; match == -1 && start < num_piles; start++) {
        for (i = 0; match == -1 && i < 2; i++) {
            place = start + diff[i];
            if (place >= 0 && MATCH(place, start)) {
                assert(!EMPTY(start));
                PUSH(place, POP(start));
                match = start;
            }
        }
    }
    if (match >= 0) {
        if (EMPTY(match)) {
            for (start = match; start < num_piles - 1; start++) {
                pile[start] = pile[start + 1];
            }
            pile[start].top = 0;
            num_piles--;
        }
        replace(place);
    }
}

/* Main function */
int main() {
    card_t card;
    int i;
    while (scanf(" %s", card) != EOF) {
        if (card[0] == '#') {
            break;
        }
        memset(pile, 0, MAX_CARDS * sizeof (pile_t));
        num_piles = 0;       
        NEW_PUSH(card);
        for (i = 1; i < MAX_CARDS; i++) {
            assert(scanf(" %s", card) != EOF);
            NEW_PUSH(card);
            replace(num_piles - 1); 
        }
        printf("%d pile%s remaining:", num_piles, (num_piles > 1 ? "s" : ""));
        for (i = 0; i < num_piles; i++) {
            printf(" %d", pile[i].top);
        }
        printf("\n");
    }
    return 0;
}
