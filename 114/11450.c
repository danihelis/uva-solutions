/* 11450
 * Wedding Shopping
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_MONEY   210
#define MAX_GARMENT 20
#define MAX_MODEL   20
#define IMPOSSIBLE  -1

int price[MAX_GARMENT][MAX_MODEL];
int models[MAX_GARMENT];
int num_garments;

/* Get the most expensive garment models respecting the budget limit */
int get_maximum_budget(int budget) {
    int current[MAX_MONEY], remain[MAX_MONEY], min_cost, i, j, k;
    memset(current, 0, budget * sizeof (int));
    for (i = num_garments - 1, min_cost = 0; i >= 0; i--) {
        memcpy(remain, current, budget * sizeof (int));
        if (min_cost + price[i][0] > budget) {
            return IMPOSSIBLE;
        }
        for (j = (i == 0 ? budget : price[i][0] + min_cost); j <= budget; j++) {
            current[j] = 0;
            for (k = 0; k < models[i] && j - price[i][k] >= min_cost; k++) {
                int left = j - price[i][k];
                int total = price[i][k] + remain[left];
                if (total > current[j]) {
                    current[j] = total;
                }
            }
        }
        min_cost += price[i][0];
    }
    return current[budget];
}

/* Compare two integers in order to sort them */
int compare_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, j, budget;
        assert(scanf("%d %d", &budget, &num_garments) != EOF);
        for (i = 0; i < num_garments; i++) {
            assert(scanf("%d", &models[i]) != EOF);
            for (j = 0; j < models[i]; j++) {
                assert(scanf("%d", &price[i][j]) != EOF);
            }
            qsort(price[i], models[i], sizeof (int), compare_int);
        }
        budget = get_maximum_budget(budget);
        if (budget == IMPOSSIBLE) {
            printf("no solution\n");
        }
        else {
            printf("%d\n", budget);
        }
    }
    return 0;
}
