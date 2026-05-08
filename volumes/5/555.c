/* 555
 * Bridge Hands
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CARDS       52
#define NUM_PLAYERS     4
#define HAND_SIZE       13
#define INPUT_SIZE      100

typedef struct {
    char *suit, *face;
} card_t;

char order_rank[] = "SWNE";
char suit_rank[] = "CDSH";
char face_rank[] = "23456789TJQKA";

card_t hands[NUM_PLAYERS][NUM_CARDS];
int num_cards[NUM_PLAYERS];

/* Compare two cards */
int compare_cards(const void *a, const void *b) {
    card_t *x = (card_t *) a, *y = (card_t *) b;
    if (x->suit == y->suit) return x->face - y->face;
    return x->suit - y->suit;
}

/* Main function */
int main() {
    char input[INPUT_SIZE];

    while (scanf(" %s", input) == 1 && input[0] != '#') {
        char *order, *s;
        int i, j, player;

        order = strchr(order_rank, input[0]);
        assert(order != NULL);
        player = (order - order_rank + 1) % NUM_PLAYERS;

        for (i = 0; i < NUM_PLAYERS; i++) {
            num_cards[i] = 0;
        }

        for (i = 0; i < 2; i++) {
            assert(scanf(" %s", input) == 1);

            for (s = input; *s != 0; s++) {
                card_t *c = &hands[player][num_cards[player]++];
                player = (player + 1) % NUM_PLAYERS;

                c->suit = strchr(suit_rank, *s);
                s++;
                c->face = strchr(face_rank, *s);
                assert(c->suit != NULL && c->face != NULL);
            }
        }

        for (i = 0; i < NUM_PLAYERS; i++) {
            qsort(hands[i], num_cards[i], sizeof (card_t), compare_cards);

            printf("%c:", order_rank[i]);
            for (j = 0; j < num_cards[i]; j++) {
                card_t *c = &hands[i][j];
                printf(" %c%c", *c->suit, *c->face);
            }
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
