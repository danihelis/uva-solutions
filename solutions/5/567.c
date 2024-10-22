/* 567
 * Risk
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       20
#define INFINITY    9999

char link[MAX_N][MAX_N];
int distance[MAX_N][MAX_N];

/* Compute all distances */
void compute_all_distances() {
    int i, j, k;
    for (i = 0; i < MAX_N; i++)
        for (j = 0; j < MAX_N; j++)
            distance[i][j] = link[i][j] ? 1 : INFINITY;
    for (k = 0; k < MAX_N; k++)
        for (i = 0; i < MAX_N; i++)
            for (j = 0; j < MAX_N; j++) {
                int shortcut = distance[i][k] + distance[k][j];
                if (shortcut < distance[i][j])
                    distance[i][j] = shortcut;
            }
}

/* Main function */
int main() {
    int test, i, j, n;
    for (test = 1; scanf("%d", &n) != EOF; test++) {
        memset(link, 0, MAX_N * MAX_N);
        for (i = 0; i < MAX_N - 1; i++) {
            if (i > 0)
                assert(scanf("%d", &n) != EOF);
            for (; n > 0; n--) {
                assert(scanf("%d", &j) != EOF);
                j--;
                link[i][j] = link[j][i] = 1;
            }
        }
        compute_all_distances();
        assert(scanf("%d", &n) != EOF);
        printf("Test Set #%d\n", test);
        for (; n > 0; n--) {
            assert(scanf("%d %d", &i, &j) != EOF);
            printf("%2d to %2d: %d\n", i, j, distance[i - 1][j - 1]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
