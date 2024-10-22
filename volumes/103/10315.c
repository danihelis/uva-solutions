/*
 * 10315
 * Poker Hands
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_VALUES 13
#define NUM_CARDS 5
#define VALUE(x) (isdigit(x) ? (x) - '2' : \
        (x) == 'T' ? 8 : \
        (x) == 'J' ? 9 : \
        (x) == 'Q' ? 10 : \
        (x) == 'K' ? 11 : \
        (x) == 'A' ? 12 : -1)

#define ACE 12 /* VALUE('A') */
#define FIVE 3 /* VALUE('5') */

typedef enum {
    BLACK = 0,
    WHITE = 1,
    TIE
} player_t;

typedef enum {
    HIGH_CARD = 0,
    PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
} combination_t;

typedef struct {
    char suit;
    short value;
    combination_t type;
} card_t;

typedef struct {
    card_t cards[NUM_CARDS];
    combination_t poker_value;
} hand_t;


/* Sort a hand by value only */
int sort_by_value(const void *a, const void *b) {
    return ((card_t *) b)->value - ((card_t *) a)->value;
}


/* Determine poker combination type */
void determine_combination_type(hand_t *hand) {
    char count[MAX_VALUES];
    int i;

    qsort(hand->cards, NUM_CARDS, sizeof (card_t), sort_by_value);

    /* Check for repetitions */
    memset(count, 0, MAX_VALUES);
    for (i = 0; i < NUM_CARDS; i++) {
        count[hand->cards[i].value]++;
    }
    hand->poker_value = HIGH_CARD;
    for (i = 0; i < NUM_CARDS; i++) {
        switch (count[hand->cards[i].value]) {
            case 2:
                hand->cards[i].type = PAIR;
                i += 1; /* skip next repeated card */
                if (hand->poker_value == PAIR) {
                    hand->poker_value = TWO_PAIRS;
                }
                else if (hand->poker_value == THREE_OF_A_KIND) {
                    hand->poker_value = FULL_HOUSE;
                }
                else {
                    hand->poker_value = PAIR;
                }
                break;
            case 3:
                hand->cards[i].type = THREE_OF_A_KIND;
                i += 2; /* skip next two repeated cards */
                if (hand->poker_value == PAIR) {
                    hand->poker_value = FULL_HOUSE;
                }
                else {
                    hand->poker_value = THREE_OF_A_KIND;
                }
                break;
            case 4:
                hand->cards[i].type = FOUR_OF_A_KIND;
                i += 3; /* skip next three repeated cards */
                hand->poker_value = FOUR_OF_A_KIND;
                break;
        }
    }

    if (hand->poker_value != HIGH_CARD) {
        return;
    }

    /* Check for five equal suits */
    for (i = 1; i < NUM_CARDS && 
            hand->cards[i].suit == hand->cards[0].suit; i++)
        ;
    if (i == NUM_CARDS) {
        hand->poker_value = FLUSH;
    }

    /* Check for a sequence of consecutive values */
    for (i = 1; i < NUM_CARDS && 
            hand->cards[i - 1].value - hand->cards[i].value == 1; i++)
        ;
    /* Verify if it is the sequence (A 5 4 3 2) == A 2..5 
    if (i == 1 && hand->cards[0].value == ACE && 
            hand->cards[1].value == FIVE) {
        i = NUM_CARDS; 
    }
    */
    if (i == NUM_CARDS) {
        if (hand->poker_value == FLUSH) {
            hand->poker_value = STRAIGHT_FLUSH;
        }
        else {
            hand->poker_value = STRAIGHT;
        }
    }
}


/* Sort a hand by value and poker combination type  */
int sort_for_poker(const void *a, const void *b) {
    card_t *x = (card_t *) a, *y = (card_t *) b;
    if (x->type == y->type) {
        return y->value - x->value;
    }
    return y->type - x->type;
}

/* Compare two hands of poker and determine the winner */
player_t compare_hands(hand_t *black, hand_t *white) {
    int i;

    determine_combination_type(black);
    determine_combination_type(white);

    if (black->poker_value != white->poker_value) {
        return (black->poker_value > white->poker_value ? BLACK : WHITE);
    }

    qsort(black->cards, NUM_CARDS, sizeof (card_t), sort_for_poker);
    qsort(white->cards, NUM_CARDS, sizeof (card_t), sort_for_poker);
    
    /* Abnormal sequence A 2..5 
    if ((black->poker_value == STRAIGHT || 
                black->poker_value == STRAIGHT_FLUSH)
            && (black->cards[1].value == FIVE || 
                white->cards[1].value == FIVE)) {
        return (black->cards[1].value == FIVE ? 
                (white->cards[1].value == FIVE ? TIE : WHITE) : WHITE);
    }
    */

    for (i = 0; i < NUM_CARDS; i++) {
        if (black->cards[i].value != white->cards[i].value) {
            return (black->cards[i].value > white->cards[i].value ? 
                    BLACK : WHITE);
        }
    }
    return TIE;
}


/*  Main function */
int main() {
    hand_t hands[2];
    player_t winner;
    char card[10];

    while (scanf("%s", card) != EOF) {
        int player = 0, card_number = 0;
        do {
            hands[player].cards[card_number].value = VALUE(card[0]);
            hands[player].cards[card_number].suit = card[1];
            hands[player].cards[card_number].type = HIGH_CARD;
            card_number++;
            if (card_number >= NUM_CARDS) {
                player++;
                card_number = 0;
            }
        } while (player < 2 && scanf("%s", card) != EOF);

        winner = compare_hands(&hands[BLACK], &hands[WHITE]);
        printf("%s%s.\n", 
                (winner == BLACK ? "Black" : winner == WHITE ? "White" : "Tie"),
                (winner == TIE ? "" : " wins"));
    }

    return 0;
}
