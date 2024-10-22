/*
 * 10132
 * File Fragmentation
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define FRAGMENT_SIZE (256 * 8 + 1)
#define INPUT_SIZE (FRAGMENT_SIZE + 1)
#define MAX_FRAGMENTS (144 * 2)
#define ANY 'x'

typedef enum {
    HEAD = 0,
    TAIL = 1
} position_t;
#define NUM_POSITIONS 2

char sequence[MAX_FRAGMENTS][INPUT_SIZE];
int num_sequences;

typedef struct {
    short index[NUM_POSITIONS];
    char times[NUM_POSITIONS];
    char many;
} fragment_t;
fragment_t fragment[FRAGMENT_SIZE];

int biggest, smallest, pattern_size, entries;
char pattern[INPUT_SIZE];


/* Initialize data */
void initialize() {
    memset(fragment, 0, sizeof(fragment_t) * (FRAGMENT_SIZE));
    num_sequences = 0;
    entries = 0;
    biggest = -1;
    smallest = FRAGMENT_SIZE + 1;
}


/* Add fragment */
void add_fragment(char *input) {
    int size, k;
    
    size = strlen(input) - 1;
    entries++;
    biggest = (biggest < size ? size : biggest);
    smallest = (smallest > size ? size : smallest);
    
    input[size] = '\0';
    for (k = 0; k < fragment[size].many; k++) {
        if (strcmp(input, sequence[fragment[size].index[k]]) == 0) {
            fragment[size].times[k]++;
            return;
        }
    }

    strcpy(sequence[num_sequences], input);
    fragment[size].index[k] = num_sequences;
    fragment[size].times[k]++;
    fragment[size].many++;
    num_sequences++;
}


/* Join pieces and determine intermediate pattern */
void join_pieces() {
    int s, i, k, half;

    /* Join together */
    pattern_size = smallest + biggest;
    for (s = smallest; s <= biggest; s++) {
        for (i = 0; i < fragment[s].many; i++) {
            k = pattern_size - s;
            if (fragment[k].many == 1) {
                if (k != s) {
                    strcat(sequence[fragment[s].index[i]], sequence[fragment[k].index[0]]);
                }
                else {
                    int p = s, q;
                    for (q = 0; q < s; q++, p++) {
                        sequence[fragment[s].index[i]][p] = sequence[fragment[s].index[i]][q];
                    }
                    sequence[fragment[s].index[i]][p] = '\0';
                }
            }
            else {
                assert(fragment[k].many == 2);
                if (k == s) {
                    strcat(sequence[fragment[s].index[i]], sequence[fragment[s].index[(1 - i)]]);
                }
                else {
                    int p = s, q;
                    for (q = 0; q < k; q++, p++) {
                        char value[NUM_POSITIONS];
                        value[0] = sequence[fragment[k].index[0]][q];
                        value[1] = sequence[fragment[k].index[1]][q];
                        sequence[fragment[s].index[i]][p] = (value[0] == value[1] ? value[0] : ANY);
                    }
                    sequence[fragment[s].index[i]][p] = '\0';
                }
            }
        }
    }

    /* Create possible pattern */
    half = entries / 2;
    for (k = 0; k < pattern_size; k++) {
        int zeroes = 0, ones = 0;
        for (s = smallest; s <= biggest; s++) {
            for (i = 0; i < fragment[s].many; i++) {
                char value = sequence[fragment[s].index[i]][k];
                assert(value == '0' || value == '1' || value == ANY);
                zeroes += (value == '0' ? fragment[s].times[i] : 0);
                ones += (value == '1' ? fragment[s].times[i] : 0);
            }
        }
        pattern[k] = (zeroes > half ? '0' : ones > half ? '1' : ANY);
    }
    pattern[pattern_size] = '\0';

    /* Undo joining */
    for (s = smallest; s <= biggest; s++) {
        for (i = 0; i < fragment[s].many; i++) {
            sequence[fragment[s].index[i]][s] = '\0';
        }
    }
}


/* Verify if sequence matches the pattern */
int match_pattern(int s, short i, position_t pos, char check_complement) {
    int p, k;
    for (p = 0, k = (pos == HEAD ? 0 : pattern_size - s); p < s; p++, k++) {
        if (pattern[k] != ANY && sequence[fragment[s].index[i]][p] != pattern[k]) {
            return 0;
        }
    }
    if (!check_complement) {
        return 1;
    }
    
    k = pattern_size - s;
    if (fragment[k].many == 1) {
        return match_pattern(k, 0, (pos == HEAD ? TAIL : HEAD), 0);
    }
    else if (k == s) {
        return match_pattern(k, 1 - i, (pos == HEAD ? TAIL : HEAD), 0);
    }
    else {
        int match = 0;
        for (p = 0; !match && p < fragment[k].many; p++) {
            match = match_pattern(k, p, (pos == HEAD ? TAIL : HEAD), 0);
        }
        return match;
    }
}


/* Set the pattern according to a fragment placement, and deduce the other part */
void set_pattern(int s, short i, position_t pos) {
    int k = pattern_size - s, j = 0;
    if (fragment[k].many > 1) {
        if (k == s) {
            j = 1 - i;
        }
        else if (!match_pattern(k, j, (pos == HEAD ? TAIL : HEAD), 0)) {
            j = 1;
        }
    }
    strcpy(pattern, sequence[(pos == HEAD ? fragment[s].index[i] : fragment[k].index[j])]);
    strcat(pattern, sequence[(pos == TAIL ? fragment[s].index[i] : fragment[k].index[j])]);
}


/* Find definitive pattern */
void find_definitive_pattern() {
    int s, i, p, half;
    half = entries / 2;
    for (s = biggest; s >= half; s--) {
        for (i = 0; i < fragment[s].many; i++) {
            for (p = 0; p < NUM_POSITIONS; p++) {
                if (!match_pattern(s, i, p, 1)) {
                    set_pattern(s, i, 1 - p);
                    return;
                }
            }
        }
    }
    /* Any will do */
    set_pattern(biggest, 0, HEAD);
}


/* Main function */
int main() {
    char input[INPUT_SIZE];
    int tests, current_test;

    assert(fgets(input, INPUT_SIZE, stdin) != NULL);
    tests = atoi(input);
    for (current_test = 0; current_test < tests; current_test++) {
        (current_test == 0 ? assert(fgets(input, INPUT_SIZE, stdin) != NULL) : (void) printf("\n"));
        initialize();

        while (fgets(input, INPUT_SIZE, stdin) != NULL) {
            if (input[0] == '\n') {
                break;
            }
            add_fragment(input);
        }
        join_pieces();
        find_definitive_pattern();

        printf("%s\n", pattern);
    }
    return 0;
}

