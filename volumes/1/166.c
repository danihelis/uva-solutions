/* 166
 * Making Change
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COINS 6
#define MAX_VALUE 100
#define MAX_CHANGE 40
#define INFINITY 1000000

int coin[MAX_COINS] = {1, 2, 4, 10, 20, 40};
int num_coins[MAX_COINS];

#define MIN(x, y) ((x) < (y) ? (x) : (y))

/* Return the number of coins used to return the change without other transactions */
int coins_in_return(int value) {
    int i, total;
    for (i = MAX_COINS - 1, total = 0; i >= 0; i--) {
        total += value / coin[i];
        value = value % coin[i];
    }
    return total;
}

/* Return the number of coins in the best (minimum) transaction */
int best_change(int index, int value, int limit) {
    if (index < 0) {
        return (value == 0 ? 0 : value > 0 ? INFINITY : coins_in_return(-value));
    }
    else {
        int k, minimum;
        for (k = 0, minimum = INFINITY; k <= num_coins[index] && k < limit; k++) {
            int best = best_change(index - 1, value - k * coin[index], limit - k);
            if (best + k < minimum) {
                minimum = best + k;
                limit = minimum;
            }
        }
        return minimum;
    }
}

/* Main function */
int main() {
    int i, all_zeroes, value, cents;
    while (1) {
        for (i = 0, all_zeroes = 1; i < MAX_COINS; i++) {
            assert(scanf("%d", &num_coins[i]) != EOF);
            all_zeroes = all_zeroes && num_coins[i] == 0;
        }
        if (all_zeroes) {
            break;
        }
        assert(scanf("%d.%d", &value, &cents) != EOF);
        printf("%3d\n", best_change(MAX_COINS - 1, value * 20 + cents / 5, INFINITY));
    }
    return 0;
}
