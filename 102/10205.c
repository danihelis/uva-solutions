/*
 * 10205
 * Stack 'em Up
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Useful macros */
#define STRING_LENGTH 15
#define NUM_SUITS 4
#define NUM_VALUES 13
typedef char string_t[STRING_LENGTH];
string_t suit[NUM_SUITS] = {"Clubs", "Diamonds", "Hearts", "Spades"};
string_t value[NUM_VALUES] = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
        "Jack", "Queen", "King", "Ace"};
#define PRINT_CARD(x) printf("%s of %s\n", value[(x) % 13], suit[(x) / 13])

#define INPUT_SIZE 1024
char input[INPUT_SIZE];

#define MAX_SHUFFLES 100
#define NUM_CARDS 52
int shuffle[MAX_SHUFFLES][NUM_CARDS];
int num_shuffles;
int deck[NUM_CARDS], new_deck[NUM_CARDS];


/* Read shuffle */
void read_shuffles() {
    int i, read;
    char *number;
    
    assert(fgets(input, INPUT_SIZE, stdin) != NULL);
    num_shuffles = atoi(input);

    for (i = 0; i < num_shuffles; i++) {
        read = 0;
        while (read < NUM_CARDS) {
            assert(fgets(input, INPUT_SIZE, stdin) != NULL);
            number = strtok(input, " \n");
            while (number != NULL) {
                shuffle[i][read++] = atoi(number) - 1;
                number = strtok(NULL, " \n");
            }
        }
        assert(read == NUM_CARDS);
    }
}


/* Main function */
int main() {
    int total_entries, entry;
    int i;
    
    assert(fgets(input, INPUT_SIZE, stdin) != NULL);
    total_entries = atoi(input);
    for (entry = 0; entry < total_entries; entry++) {
        if (entry == 0) {
            assert(fgets(input, INPUT_SIZE, stdin) != NULL);
        }
        else {
            printf("\n");
        }

        read_shuffles();

        for (i = 0; i < NUM_CARDS; i++) {
            deck[i] = i;
        }
        while (fgets(input, INPUT_SIZE, stdin) != NULL) {
            int s;
            if (sscanf(input, "%d", &s) == EOF) {
                break;
            }
            s--;
            for (i = 0; i < NUM_CARDS; i++) {
                new_deck[i] = deck[shuffle[s][i]];
            }
            memcpy(deck, new_deck, NUM_CARDS * sizeof (int));
        }
        for (i = 0; i < NUM_CARDS; i++) {
            PRINT_CARD(deck[i]);
        }
    }

    return 0;
}
