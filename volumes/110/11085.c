/* 11085
 * Back to the 8-Queens
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_POS     8
#define INFINITY    100

int original[NUM_POS], board[NUM_POS];
char used[NUM_POS];
int minimum;

/* Is valid until column */
int valid_board(int column) {
    int i, j;
    for (i = 1; i <= column; i++)
        for (j = 0; j < i; j++)
            if (abs(board[i] - board[j]) == i - j)
                return 0;
    return 1;
}

/* Find minimum */
void find_minimum_queen_board(int index, int cost) {
    if (index == NUM_POS) {
        if (cost < minimum)
            minimum = cost;
    }
    else {
        int i = original[index];
        board[index] = i;
        if (!used[i] && valid_board(index)) {
            used[i] = 1;
            find_minimum_queen_board(index + 1, cost);
            used[i] = 0;
        }
        for (i = 0; cost + 1 < minimum && i < NUM_POS; i++) {
            board[index] = i;
            if (!used[i] && i != original[index] && valid_board(index)) {
                used[i] = 1;
                find_minimum_queen_board(index + 1, cost + 1);
                used[i] = 0;
            }
        }
    }
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &original[0]) != EOF) {
        int i;
        for (i = 1; i < NUM_POS; i++)
            assert(scanf("%d", &original[i]) != EOF);
        for (i = 0; i < NUM_POS; i++)
            original[i]--, used[i] = 0;
        minimum = INFINITY;
        find_minimum_queen_board(0, 0);
        printf("Case %d: %d\n", ++test, minimum);
    }
    return EXIT_SUCCESS;
}
