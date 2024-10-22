/**
 * 131
 * The Psychic Poker Player
 * by Daniel Donadon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARDS 10
#define NUM_CARDS 5

typedef enum {
    straight_flush = 0,
    four_of_a_kind,
    full_house,
    flush,
    straight,
    three_of_a_kind,
    two_pairs,
    one_pair,
    highest_card
} poker_hand_t;

typedef char card_t[3];
card_t card[MAX_CARDS];
int index[NUM_CARDS], permutation[NUM_CARDS];


/* Print a poker's hand name */
void print_poker_hand_name(poker_hand_t hand) {
    switch (hand) {
        case straight_flush: printf("straight-flush"); break;
        case four_of_a_kind: printf("four-of-a-kind"); break;
        case full_house: printf("full-house"); break;
        case flush: printf("flush"); break;
        case straight: printf("straight"); break;
        case three_of_a_kind: printf("three-of-a-kind"); break;
        case two_pairs: printf("two-pairs"); break;
        case one_pair: printf("one-pair"); break;
        case highest_card: printf("highest-card"); break;
    }
    printf("\n");
}


/* Card comparison based on face */
#define VALUE_OF(c) (c == 'A' ? 14 : (c == 'K' ? 13 : (c == 'Q' ? 12 : \
                    (c == 'J' ? 11 : (c == 'T' ? 10 : c - '0')))))
int compare(int a, int b) {
    return VALUE_OF(card[index[a]][0]) - VALUE_OF(card[index[b]][0]);
}


/* Sort the indexes of a given hand (using insertion sort) */
void sort() {
    int i, j;
    memcpy(index, permutation, NUM_CARDS * sizeof (int));
    for (i = 1; i < NUM_CARDS; i++) {
        for (j = i; j > 0 && compare(j, j - 1) > 0; j--) {
            int temp = index[j];
            index[j] = index[j - 1];
            index[j - 1] = temp;
        }
    }
}


/* Gives the highest evaluation of the cards on hand */
poker_hand_t evaluate_hand() {
    int counter[NUM_CARDS], count = 0;
    int seq, flu, k;

    sort();

    /* We first count the cards repeated. The more, the best! */
    counter[count++] = 1;
    for (k = 1; k < NUM_CARDS; k++) {
        if (compare(k, k - 1) == 0) {
            counter[count - 1]++;
        }
        else {
            counter[count++] = 1;
        }
    }
    if (count == 2) { 
        return (counter[0] == 4 || counter[1] == 4 ? four_of_a_kind : full_house);
    }

    /* We look for a sequence */
    seq = 1;
    while (seq < NUM_CARDS && (VALUE_OF(card[index[seq - 1]][0]) - VALUE_OF(card[index[seq]][0]) == 1)) {
        seq++;
    }
    if (count == 5 && card[index[0]][0] == 'A' && card[index[1]][0] == '5') { /* Ace may have value of 1 here  */
        seq = 5;
    }

    /* We also look for a flush */
    flu = 1;
    while (flu < NUM_CARDS && card[index[flu - 1]][1] == card[index[flu]][1]) {
        flu++;
    }
    
    /* The best results we can achieve */
    if (flu == 5) {
        return (seq == 5 ? straight_flush : flush);
    }
    else if (seq == 5) {
        return straight;
    }
    else if (count == 3) {
        return (counter[0] == 3 || counter[1] == 3 || counter[2] == 3 ? three_of_a_kind : two_pairs);
    }
    else if (count == 4) {
        return one_pair;
    }
    return highest_card;
}


/* Try all permutations of cards */
poker_hand_t try_all_permutations(int ith) {
    int value;
    poker_hand_t hand, best_hand = highest_card;

    if (ith == NUM_CARDS) {
        return evaluate_hand();
    }

    if (ith > 0 && permutation[ith - 1] > NUM_CARDS) { /* oblied card */
        permutation[ith] = permutation[ith - 1] - 1;
        best_hand = try_all_permutations(ith + 1);
    }
    else {
        for (value = (ith == 0 ? MAX_CARDS : permutation[ith - 1]) - 1; value >= NUM_CARDS - 1 - ith; value--) {
            permutation[ith] = value;
            hand = try_all_permutations(ith + 1);
            if (hand < best_hand) {
                best_hand = hand;
            }
        }
    }
    return best_hand;
}


/* Print complete result */
void print_result(poker_hand_t best_hand) {
    int k;
    for (k = 0; k < MAX_CARDS; k++) {
        if (k % NUM_CARDS == 0) {
            printf("%s: ", (k == 0 ? "Hand" : "Deck"));
        }
        printf("%s ", card[k]);
    }
    printf("Best hand: ");
    print_poker_hand_name(best_hand);
}


/* Main */
int main() {
    while (scanf("%s", card[0]) == 1) {
        int k;
        poker_hand_t best;
        for (k = 1; k < MAX_CARDS; k++) {
            scanf("%s", card[k]);
        }
        best = try_all_permutations(0);
        print_result(best);
    }
    return 0;
}
