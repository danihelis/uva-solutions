/* 11005
 * Cheapest Base
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BASES       36

int digit_cost[MAX_BASES];

/* Compute cost for N in a given base */
int cost_on_base(int n, int b) {
    int cost = 0;
    if (n == 0)
        return digit_cost[0];
    while (n > 0) {
        int digit = n % b;
        cost += digit_cost[digit];
        n /= b;
    }
    return cost;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, num_inputs;
        for (i = 0; i < MAX_BASES; i++)
            assert(scanf("%d", &digit_cost[i]) == 1);
        assert(scanf("%d", &num_inputs) == 1);
        printf("%sCase %d:\n", test > 1 ? "\n" : "", test);
        for (; num_inputs > 0; num_inputs--) {
            int n, min_cost, solution[MAX_BASES], num_sols;
            assert(scanf("%d", &n) == 1);
            for (i = 2, min_cost = num_sols = 0; i <= MAX_BASES; i++) {
                int cost = cost_on_base(n, i);
                if (cost < min_cost || num_sols == 0)
                    solution[0] = i, min_cost = cost, num_sols = 1;
                else if (cost == min_cost)
                    solution[num_sols++] = i;
            }
            printf("Cheapest base(s) for number %d:", n);
            for (i = 0; i < num_sols; i++)
                printf(" %d", solution[i]);
            puts("");
        }
    }
    return EXIT_SUCCESS;
}
