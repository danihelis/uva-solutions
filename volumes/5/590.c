/* 590
 * Always on the run
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CITIES  10
#define MAX_DAYS    30
#define IMPOSSIBLE  -1

int cost[MAX_CITIES][MAX_CITIES][MAX_DAYS];
int cycle[MAX_CITIES][MAX_CITIES];
int num_cities, num_flights;

/* Determine the best cost for the many flights */
int best_cost() {
    int solution[MAX_CITIES], previous[MAX_CITIES];
    int day, flight, city, next, limit;
    memset(solution, 0, num_cities * sizeof (int));
    for (day = num_flights - 1; day >= 0; day--) {
        memcpy(previous, solution, num_cities * sizeof (int));
        limit = (day == 0 ? 1 : num_cities);
        for (city = 0; city < limit; city++) {
            int flight_cost, best = IMPOSSIBLE;
            for (next = (day == num_flights - 1 ? num_cities - 1 : 0); next < num_cities; next++) {
                if (city == next || previous[next] == IMPOSSIBLE) {
                        continue;
                }
                flight = day % cycle[city][next];
                if (cost[city][next][flight] == 0) {
                    continue;
                }
                flight_cost = cost[city][next][flight] + previous[next];
                if (best == IMPOSSIBLE || flight_cost < best) {
                    best = flight_cost;
                }
            }
            solution[city] = best;
        }
    }
    return solution[0];
}

/* Main function */
int main() {
    int test = 1;
    while (scanf("%d %d", &num_cities, &num_flights) != EOF && num_cities > 0) {
        int i, j, k, solution;
        for (i = 0; i < num_cities; i++) {
            for (j = 0; j < num_cities; j++) {
                if (i == j) {
                    continue;
                }
                assert(scanf("%d", &cycle[i][j]) != EOF);
                for (k = 0; k < cycle[i][j]; k++) {
                    assert(scanf("%d", &cost[i][j][k]) != EOF);
                }
            }
        }
        printf("Scenario #%d\n", test++);
        solution = best_cost();
        if (solution == IMPOSSIBLE) {
            printf("No flight possible.\n\n");
        }
        else {
            printf("The best flight costs %d.\n\n", solution);
        }
    }
    return 0;
}
