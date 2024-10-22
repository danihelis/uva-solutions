/* 11517
 * Exact Change
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COINS 100
#define MAX_VALUE 10010
#define INFINITY 10000000

typedef struct {
    int value, coins;
    char set;
} combination_t, *combination_p;

combination_t table[MAX_COINS][MAX_VALUE];
int coin[MAX_COINS];
int num_coins;

#define CEIL(x, y) (((x) + (y) - 1) / (y))

int compare_int(const void *a, const void *b) {
    return *((int *) b) - *((int *) a);
}

int best_combination(int money, int index, int limit, int *coins, int *value) {
    if (index < 0 || money <= 0) {
        *coins = 0;
        *value = 0;
    }
    else if (table[index][money].set) {
        *coins = table[index][money].coins;
        *value = table[index][money].value;
    }
    else {
        int k, min_coins = INFINITY, min_value = INFINITY;
        for (k = 0; k <= 1 && k * coin[index] <= limit; k++) {
            int add = k * coin[index];
            if (best_combination(money - add, index - 1, limit - add, coins, value) &&
                    (*value + add < min_value || 
                     (*value + add == min_value && *coins + k < min_coins))) {
                min_coins = *coins + k;
                min_value = *value + add;
                limit = min_value;
            }
        }
        *value = table[index][money].value = min_value;
        *coins = table[index][money].coins = min_coins;
        table[index][money].set = 1;
    }
    return (*value >= money);
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, money, coins, value;
        assert(scanf("%d %d", &money, &num_coins) != EOF);
        for (i = 0; i < num_coins; i++) {
            assert(scanf("%d", &coin[i]) != EOF);
        }
        qsort(coin, num_coins, sizeof (int), compare_int);
        memset(table, 0, sizeof (combination_t) * MAX_COINS * MAX_VALUE);
        assert(best_combination(money, num_coins - 1, INFINITY, &coins, &value));
        printf("%d %d\n", value, coins);
    }
    return 0;
}
