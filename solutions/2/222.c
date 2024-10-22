/* 222
 * Budget Travel
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STATIONS    51
#define MINIMUM_COST    2.00

typedef struct {
    double distance, price;
} station_t, *station_p;

station_t station[MAX_STATIONS];
double destination, capacity, milage, best, init_cost;
int num_stations;

/* Compute minimum cost to perform trip */
void compute_minimum_cost(int next_point, double gas, double location, double cost) {
    double can_reach = gas * milage + location;
    if (can_reach >= destination) {
        if (best < 0 || cost < best ) {
            best = cost;
        }
    }
    else {
        for (; next_point < num_stations && 
                can_reach >= station[next_point].distance; next_point++) {
            station_p s = &station[next_point];
            double gas_left = gas - (s->distance - location) / milage;
            if (can_reach < station[next_point + 1].distance || gas_left <= capacity / 2) {
                double new_cost = cost + MINIMUM_COST + (capacity - gas_left) * s->price / 100;
                compute_minimum_cost(next_point + 1, capacity, s->distance, new_cost);
            }
        }
    }
}

/* Main function */
int main() {
    int test = 0, i;
    while (scanf("%lf", &destination) != EOF && destination >= 0) {
        assert(scanf("%lf %lf %lf %d", &capacity, &milage, &init_cost, &num_stations) != EOF);
        for (i = 0; i < num_stations; i++) {
            assert(scanf("%lf %lf", &station[i].distance, &station[i].price) != EOF);
        }
        station[num_stations].distance = destination, best = -1;
        compute_minimum_cost(0, capacity, 0, init_cost);
        assert(best >= 0);
        printf("Data Set #%d\nminimum cost = $%0.2f\n", ++test, best);
    }
    return 0;
}
