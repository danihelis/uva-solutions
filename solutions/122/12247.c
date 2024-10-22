/* 12247
 * Jollo
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_PLAYERS 2
#define NUM_CARDS   3
#define NUM_USED    (NUM_PLAYERS * NUM_CARDS - 1)
#define MAX_VALUE   52

/* Main function */
int main() {
    int card[NUM_PLAYERS][NUM_CARDS], used[NUM_USED];
    while (scanf("%d", &card[0][0]) != EOF && card[0][0] > 0) {
        int i, k, rounds;
        used[0] = card[0][0];
        for (k = 0; k < 2; k++) {
            for (i = 1; i < NUM_CARDS; i++) {
                assert(scanf("%d", &card[k][i - k]) != EOF);
                used[k * NUM_CARDS + i - k] = card[k][i - k];
            }
            if (k == 1 && card[k][0] < card[k][1]) {
                int swap = card[k][0];
                card[k][0] = card[k][1];
                card[k][1] = swap;
            }
        }
        for (k = 0, rounds = 0; k < NUM_CARDS - 1; k++) {
            int *best = &card[0][0], prince = card[1][k];
            for (i = 1; i < NUM_CARDS; i++) {
                int *this = &card[0][i];
                if (*best == 0 || (*this > prince && (*this < *best || *best < prince)) ||
                        (*this > 0 && *this < prince && *this < *best && *best < prince)) {
                    best = this;
                }
            }
            rounds += *best < prince;
            *best = 0;
        }
        if (rounds == 0) {
            printf("-1\n");
        }
        else {
            int min = rounds == 2 ? 0 : card[0][0] + card[0][1] + card[0][2], is_used = 1;
            while (is_used) {
                min++;
                for (i = 0, is_used = 0; i < NUM_USED; i++) {
                    is_used |= used[i] == min;
                }
            }
            printf("%d\n", min <= MAX_VALUE ? min : -1);
        }

    }
    return 0;
}
