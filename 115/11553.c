/* 11553
 * Grid Game
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     8
#define MAX_N       (1 << MAX_DIM)

#define MAX_INT      0x7fffffff
#define MIN_INT      0x80000000

int matrix[MAX_DIM][MAX_DIM], best[MAX_N][MAX_N];
char computed[MAX_N][MAX_N];
int dim;

/* Compute best solution with memoization */
int get_best(int rows, int cols) {
    if (computed[rows][cols])
        return best[rows][cols];
    else if (rows == 0 && cols == 0) {
        computed[rows][cols] = 1;
        return (best[rows][cols] = 0);
    }
    else {
        int r, c, opt, subopt;
        for (r = 0, opt = MIN_INT; r < dim; r++) {
            int ir = 1 << r;
            if ((ir & rows) != 0) {
                for (c = 0, subopt = MAX_INT; c < dim; c++) {
                    int ic = 1 << c;
                    if ((ic & cols) != 0) {
                        int val = get_best(rows & ~ir, cols & ~ic) + 
                                matrix[r][c];
                        if (val < subopt)
                            subopt = val;
                    }
                }
                if (subopt > opt)
                    opt = subopt;
            }
        }
        computed[rows][cols] = 1;
        return (best[rows][cols] = opt);
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int r, c, n;
        assert(scanf("%d", &dim) == 1);
        for (r = 0; r < dim; r++)
            for (c = 0; c < dim; c++)
                assert(scanf("%d", &matrix[r][c]) == 1);
        n = 1 << dim;
        memset(computed, 0, n * MAX_N);
        printf("%d\n", get_best(n - 1, n - 1));
    }
    return EXIT_SUCCESS;
}
