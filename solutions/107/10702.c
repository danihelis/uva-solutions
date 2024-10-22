/* 10702
 * Travelling Salesman
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CITIES  100

int cost[MAX_CITIES][MAX_CITIES];
char can_go[MAX_CITIES];
int num_cities;

/* Compute the best profit the salesman can earn from the start */
int get_most_profit(int start, int turns) {
    int profit[MAX_CITIES], previous[MAX_CITIES];
    int i, j, t;
    memset(profit, 0, num_cities * sizeof (int));
    for (t = turns - 1; t >= 0; t--) {
        memcpy(previous, profit, num_cities * sizeof (int));
        for (i = 0; i < num_cities; i++) {
            int best_profit = 0;
            for (j = 0; j < num_cities; j++) {
                if (i != j && (t < turns - 1 || can_go[j])) {
                    int new_profit = previous[j] + cost[i][j];
                    if (new_profit > best_profit) {
                        best_profit = new_profit;
                    }
                }
            }
            profit[i] = best_profit;
        }
    }
    return profit[start];
}

/* Main function */
int main() {
    int end_points, turns, start_point;
    while (scanf("%d %d %d %d", &num_cities, &start_point, &end_points, &turns) != EOF &&
            num_cities > 0) {
        int i, j;
        for (i = 0; i < num_cities; i++) {
            for (j = 0; j < num_cities; j++) {
                assert(scanf("%d", &cost[i][j]) != EOF);
            }
        }
        memset(can_go, 0, num_cities);
        for (i = 0; i < end_points; i++) {
            assert(scanf("%d", &j) != EOF);
            can_go[--j] = 1;
        }
        printf("%d\n", get_most_profit(--start_point, turns));
    }
    return 0;
}
