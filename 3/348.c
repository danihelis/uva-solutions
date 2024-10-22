/* 348
 * Optimal Array Multiplication Sequence
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION   10

struct {
    int total, index;
} matrix[MAX_DIMENSION][MAX_DIMENSION];

int dimension[MAX_DIMENSION + 1], n;

/* Compute best matrix multiplication chain */
void compute_chain() {
    int i, j, k, p;
    for (i = 0; i < n; i++) {
        matrix[i][i].total = 0, matrix[i][i].index = i;
    }
    for (k = 1; k < n; k++) {
        for (i = 0, j = k; i < n && j < n; i++, j++) {
            int best = 0, index = -1;
            for (p = 0; p < k; p++) {
                int total = matrix[i][i + p].total + matrix[i + p + 1][j].total;
                total += dimension[i] * dimension[i + p + 1] * dimension[j + 1];
                if (total < best || index == -1) {
                    best = total, index = p;
                }
            }
            matrix[i][j].total = best, matrix[i][j].index = index;
        }
    }

#if 0
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            (i > j ? printf("%5s ", "") : printf("%5d ", matrix[i][j].total));
        }
        printf("\n");
    }
#endif
}

/* Print multiplication chain using recursion to parenthize */
void print_chain(int i, int j) {
    if (i == j) {
        printf("A%d", i + 1);
    }
    else {
        printf("(");
        print_chain(i, i + matrix[i][j].index);
        printf(" x ");
        print_chain(i + 1 + matrix[i][j].index, j);
        printf(")");
    }
}

/* Main function */
int main() {
    int i, chain = 0;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (i = 0; i < n; i++) {
            assert(scanf("%d %d", &dimension[i], &dimension[i + 1]) != EOF);
        }
        compute_chain();
        printf("Case %d: ", ++chain);
        print_chain(0, n - 1);
        printf("\n");
    }

    return 0;
}
