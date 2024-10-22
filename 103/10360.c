/* 10360
 * Rat Attack
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION   1026
#define MAX_SQUARE      (MAX_DIMENSION * MAX_DIMENSION)

#define MAX(x, y)       ((x) > (y) ? (x) : (y))
#define MIN(x, y)       ((x) < (y) ? (x) : (y))

int population[MAX_DIMENSION][MAX_DIMENSION];
int *queue[MAX_SQUARE];
int radius, top_queue;

/* Add rat population */
void add_population(int x, int y, int pop) {
    int i, j, min_row, max_row, min_col, max_col;
    min_row = MAX(x - radius, 0);
    min_col = MAX(y - radius, 0);
    max_row = MIN(x + radius + 1, MAX_DIMENSION);
    max_col = MIN(y + radius + 1, MAX_DIMENSION);
    for (i = min_row; i < max_row; i++) {
        for (j = min_col; j < max_col; j++) {
            if (population[i][j] == 0) {
                queue[top_queue++] = &population[i][j];
            }
            population[i][j] += pop;
        }
    }
}

/* Return cell with largest population */
int * get_largest() {
    int t, *largest = NULL;
    for (t = 0; t < top_queue; t++) {
        if (largest == NULL || *queue[t] > *largest || 
                (*queue[t] == *largest && queue[t] < largest)) {
            largest = queue[t];
        }
    }
    return largest;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int num_populations, x, y, pop, *solution;
        memset(population, 0, MAX_SQUARE * sizeof (int));
        top_queue = 0;
        assert(scanf("%d %d", &radius, &num_populations) != EOF);
        for (; num_populations > 0; num_populations--) {
            assert(scanf("%d %d %d", &x, &y, &pop) != EOF);
            add_population(x, y, pop);
        }
        solution = get_largest();
        assert(solution != NULL);
        printf("%d %d %d\n", (int) (solution - population[0]) / MAX_DIMENSION, 
                (int) (solution - population[0]) % MAX_DIMENSION, 
                *solution);
    }
    return 0;
}
