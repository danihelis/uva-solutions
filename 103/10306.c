/* 10306
 * e-Coins
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_COINS 40
#define MAX_VALUE 300
#define INFINITY 1000

typedef struct {
    int x, y;
} coin_t, *coin_p;

coin_t value[MAX_COINS];
int num_coins;

#define SET(d,xv,yv) (d).x = (xv); (d).y = (yv)

/* Get the minimum coins to complete the required amount */
int get_minimum(int index, coin_t demand, int limit) {
    if (index < 0) {
        return (demand.x == 0 && demand.y == 0 ? 0 : INFINITY);
    }
    else {
        int k;
        long minimum;
        for (k = 0, minimum = INFINITY; k < limit; k++) {
            long obtain;
            coin_t new_demand;
            SET(new_demand, demand.x - k * value[index].x, demand.y - k * value[index].y);
            if (new_demand.x < 0 || new_demand.y < 0) {
                break;
            }
            obtain = get_minimum(index - 1, new_demand, limit - k);
            if (obtain + k < minimum) {
                minimum = obtain + k;
                limit = minimum;
            }
        }
        return minimum;
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, j, money, ecoin, best, minimum;
        assert(scanf("%d %d", &num_coins, &money) != EOF);
        for (i = 0; i < num_coins; i++) {
            assert(scanf("%d %d", &value[i].x, &value[i].y) != EOF);
        }
        for (i = 0, j = money, minimum = INFINITY; i <= money; i++) {
            ecoin = money * money - i * i;
            while (ecoin < j * j) {
                j--;
            }
            if (ecoin == j * j) {
                coin_t demand;
                SET(demand, i, j);
                best = get_minimum(num_coins - 1, demand, minimum);
                if (best < minimum) {
                    minimum = best;
                }
            }
        }
        if (minimum == INFINITY) {
            printf("not possible\n");
        }
        else {
            printf("%d\n", minimum);
        }
    }
    return 0;
}
