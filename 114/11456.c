/* 11456
 * Trainsorting
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CARS 2000

typedef struct car_s {
    int front_chain, rear_chain;
    int weight;
} car_t, *car_p;

car_t car[MAX_CARS];
int num_cars;

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, j, best_value;
        assert(scanf("%d", &num_cars) != EOF);
        for (i = 0; i < num_cars; i++) {
            assert(scanf("%d", &car[i].weight) != EOF);
            car[i].front_chain = 0, car[i].rear_chain = 0;
        }
        for (i = num_cars - 1, best_value = 0; i >= 0; i--) {
            for (j = i - 1; j >= 0; j--) {
                if (car[i].weight < car[j].weight && car[i].front_chain >= car[j].front_chain) {
                    car[j].front_chain = car[i].front_chain + 1;
                }
                if (car[i].weight > car[j].weight && car[i].rear_chain >= car[j].rear_chain) {
                    car[j].rear_chain = car[i].rear_chain + 1;
                }
            }
            if (car[i].front_chain + car[i].rear_chain >= best_value) {
                best_value = car[i].front_chain + car[i].rear_chain + 1;
            }
        }
        printf("%d\n", best_value);
    }
    return 0;
}
