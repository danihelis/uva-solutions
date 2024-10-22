/* 457
 * Linear Cellular Automata
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_DISHES      40
#define MIDDLE_DISH     19
#define NUM_DAYS        50
#define DNA_SIZE        10
#define NUM_DENSITIES   4

char density[] = " .xW";
char dish[NUM_DISHES + 1], new_dish[NUM_DISHES + 1];
int dna[DNA_SIZE];

/* Get the density of a dish */
int density_of(int i) {
    int k;
    for (k = 0; k < NUM_DENSITIES; k++) {
        if (dish[i] == density[k]) {
            return k;
        }
    }
    assert(NULL);
    return -1;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    dish[NUM_DISHES] = 0, new_dish[NUM_DISHES] = 0;
    for (; num_tests > 0; num_tests--) {
        int i, d;
        for (i = 0; i < DNA_SIZE; i++) {
            assert(scanf("%d", &dna[i]) != EOF);
        }
        memset(new_dish, density[0], NUM_DISHES);
        new_dish[MIDDLE_DISH] = density[1];
        printf("%s\n", new_dish);
        for (d = 1; d < NUM_DAYS; d++) {
            memcpy(dish, new_dish, NUM_DISHES);
            for (i = 0; i < NUM_DISHES; i++) {
                int sum = density_of(i) + (i > 0 ? density_of(i - 1) : 0) + 
                    (i < NUM_DISHES - 1 ? density_of(i + 1) : 0);
                new_dish[i] = density[dna[sum]];
            }
            printf("%s\n", new_dish);
        }
        if (num_tests > 1) {
            printf("\n");
        }
    }
    return 0;
}
