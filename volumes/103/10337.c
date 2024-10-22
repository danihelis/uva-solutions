/* 10337
 * Flight Planner
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_OPTIONS 3
#define NUM_ALTITUDES 10
#define MAX_DISTANCE 1000
#define IMPOSSIBLE -1

int fuel_cost[NUM_OPTIONS] = {20, 30, 60};
int wind[MAX_DISTANCE][NUM_ALTITUDES];
int distance;

/* Calculate the minimum consumption of fuel to travel */
int calculate_minimum_fuel() {
    int i, j, k, consumption[MAX_DISTANCE + 1][NUM_ALTITUDES + 1];
    for (i = 0; i <= NUM_ALTITUDES; i++) {
        consumption[distance][i] = (i == 0 ? 0 : IMPOSSIBLE);
    }
    for (i = 0; i < distance; i++) {
        consumption[i][NUM_ALTITUDES] = IMPOSSIBLE;
    }
    for (i = distance - 1; i >= 0; i--) {
        for (j = 0; j < NUM_ALTITUDES; j++) {
            int minimum = IMPOSSIBLE;
            for (k = 0; k < NUM_OPTIONS; k++) {
                int cost, next = j + k - 1;
                if (next < 0 || consumption[i + 1][next] == IMPOSSIBLE) {
                    continue;
                }
                cost = consumption[i + 1][next] + fuel_cost[k] - wind[i][j];
                if (minimum == IMPOSSIBLE || cost < minimum) {
                    minimum = cost;
                }
            }
            consumption[i][j] = minimum;
        }
    }
    return consumption[0][0];
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, j;
        assert(scanf("%d", &distance) != EOF);
        distance /= 100;
        for (j = NUM_ALTITUDES - 1; j >= 0; j--) {
            for (i = 0; i < distance; i++) {
                assert(scanf("%d", &wind[i][j]) != EOF);
            }
        }
        printf("%d\n\n", calculate_minimum_fuel());
    }
    return 0;
}
