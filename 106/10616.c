/* 10616
 * Divisible Group Sums
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       200
#define MAX_MOD     20
#define MAX_COMB    10

int vector[MAX_N], size;

#define COPY(copy,orig,rows,cols)   do { \
        int i; \
        for (i = 0; i < rows; i++) \
            memcpy(copy[i], orig[i], sizeof (int) * cols); \
    } while (0)

/* Dynamic programming */
int find_combinations(int D, int M) {
    int matrix[MAX_COMB][MAX_MOD], previous[MAX_COMB][MAX_MOD];
    int i, k, d, m;
    for (i = 0; i < M; i++)
        memset(matrix[i], 0, sizeof (int) * D);
    for (i = 0; i < size; i++) {
        int rem = vector[i] % D;
        if (rem < 0)
            rem += D;
        COPY(previous, matrix, M, D);
        for (d = 0; d < D; d++)
            matrix[0][d] = (rem == d ? 1 : 0) + previous[0][d];
        for (m = 1; m < M; m++)
            for (d = 0, k = (D - rem) % D; d < D; d++, k = (k + 1) % D)
                matrix[m][d] = previous[m - 1][k] + previous[m][d];
    }
    return matrix[M - 1][0];
}

/* Main function */
int main() {
    int set = 0, num_queries;
    while (scanf("%d %d", &size, &num_queries) != EOF && size > 0) {
        int i;
        printf("SET %d:\n", ++set);
        for (i = 0; i < size; i++)
            assert(scanf("%d", &vector[i]) != EOF);
        for (i = 0; i < num_queries; i++) {
            int d, m;
            assert(scanf("%d %d", &d, &m) != EOF);
            printf("QUERY %d: %d\n", i + 1, find_combinations(d, m));
        }
    }
    return EXIT_SUCCESS;
}
