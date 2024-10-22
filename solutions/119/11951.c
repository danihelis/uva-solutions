/* 11951
 * Area
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     100

int cost[MAX_DIM][MAX_DIM];
int rows, columns, max_cost, best_area, best_cost;

/* Find best area on a row within maximal cost */
void compute_best_row(int row[], int height) {
    int sum, i, j, area;
    for (i = j = sum = 0; j < columns; j++) {
        sum += row[j];
        for (; i <= j && sum > max_cost; i++)
            sum -= row[i];
        area = (j - i + 1) * height;
        if (area > best_area || (area == best_area && sum < best_cost))
            best_area = area, best_cost = sum;
    }
}

/* Find best area on matrix */
void compute_best_area() {
    int i, j, k;
    best_area = best_cost = 0;
    for (i = 0; i < rows; i++)
        for (k = i; k >= 0; k--) {
            if (k != i)
                for (j = 0; j < columns; j++)
                    cost[k][j] += cost[i][j];
            compute_best_row(cost[k], i - k + 1);
        }
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int i, j;
        assert(scanf("%d %d %d", &rows, &columns, &max_cost) == 3);
        for (i = 0; i < rows; i++)
            for (j = 0; j < columns; j++)
                assert(scanf("%d", &cost[i][j]) == 1);
        compute_best_area();
        printf("Case #%d: %d %d\n", test, best_area, best_cost);
    }
    return EXIT_SUCCESS;
}
