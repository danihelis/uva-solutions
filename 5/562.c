/* 562
 * Dividing coins
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COINS 100
#define MAX_VALUE 500
#define MAX_BAG (MAX_COINS * MAX_VALUE)

#define ABS_DIFF(x, y) ((x) < (y) ? (y) - (x) : (x) - (y))

typedef int bag_t[MAX_BAG];

int coin[MAX_COINS];
int num_coins;

/* Determine the maximum sum of coins for half the bag */
int get_max_half_bag(int goal) {
    bag_t bag, table;
    int i, k;
    memset(table, 0, (goal + 1) * sizeof (int));
    for (i = 0; i < num_coins; i++) {
        memcpy(bag, table, (goal + 1) * sizeof (int));
        for (k = coin[i]; k <= goal; k++) {
            int diff = k - coin[i];
            if (coin[i] + bag[diff] > table[k]) {
                table[k] = coin[i] + bag[diff];
            }
        }
    }
    return table[goal];
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, sum, half, best;
        assert(scanf("%d", &num_coins) != EOF);
        for (i = 0, sum = 0; i < num_coins; i++) {
            assert(scanf("%d", &coin[i]) != EOF);
            sum += coin[i];
        }
        half = sum / 2;
        best = get_max_half_bag(half);
        printf("%d\n", ABS_DIFF(best, half) + ABS_DIFF(sum - best, half));
    }
    return 0;
}
