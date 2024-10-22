/* 855
 * Lunch in Grid City
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       1000

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int sum[2][MAX_N];
        int k, i, n, max[2], best_cost[2], best_value[2];
        assert(scanf("%d %d %d", &max[0], &max[1], &n) == 3);
        memset(sum, 0, sizeof(sum));
        for (i = 0; i < n; i++) {
            int x, y;
            assert(scanf("%d %d", &x, &y) == 2);
            sum[0][--x]++, sum[1][--y]++;
        }
        for (k = 0; k < 2; k++) {
            int partial, total, cost[MAX_N];
            for (i = partial = total = 0; i < max[k]; i++) {
                cost[i] = total;
                partial += sum[k][i];
                total += partial;
            }
            for (i = max[k] - 1, partial = total = 0; i >= 0; i--) {
                cost[i] += total;
                partial += sum[k][i];
                total += partial;
            }
            for (i = 0, best_cost[k] = 1 << 30; i < max[k]; i++)
                if (cost[i] < best_cost[k])
                    best_cost[k] = cost[i], best_value[k] = i + 1;
        }
        printf("(Street: %d, Avenue: %d)\n", best_value[0], best_value[1]);
    }
    return EXIT_SUCCESS;
}
