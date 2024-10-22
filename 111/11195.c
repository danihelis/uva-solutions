/* 11195
 * Another n-Queen Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       15
#define MAX_STRING  (MAX_N + 2)

char map[MAX_N][MAX_STRING];
int n, mod;

#if 0
char used_row[MAX_N], row[MAX_N];

/* Check for diagonals 
 * XXX: You could use bitmasks to avoid performing a repetition here!
 *      The ideia is to use 0s and 1s to mark the positions occupied
 *      in the current row/column by previous pieces that attack one
 *      diagonal. On the next row/column, these positions are shifted
 *      one position, according to the direction of the diagonal.
 *      Ex: 1 1 1 0 1 1  <- a piece is attacking a column in the n-th row
 *          1 1 0 1 1 1  <- in the (n+1)-th row, the next column is attacked
 *          1 0 1 1 1 1  <- and so on...
 */
int diagonal_intercepts(int c, int r) {
    int i;
    for (i = 0; i < c; i++)
        if (abs(row[i] - r) == c - i)
            return 1;
    return 0;
}

/* Compute solutions */
int compute_solutions(int c) {
    if (c >= n)
        return 1;
    else {
        int r, count;
        for (r = count = 0; r < n; r++)
            if (!used_row[r] && map[r][c] == '.' && 
                    !diagonal_intercepts(c, r)) {
                used_row[r] = 1;
                row[c] = r;
                count += compute_solutions(c + 1);
                used_row[r] = 0;
            }
        return count;
    }
}
#endif

/* Compute solutions (faster!) */
int compute_solutions_faster(int c, int used_rows, int used_up, 
        int used_down) {
    int free = ~(used_rows | used_up | used_down) & mod;
    if (!free)
        return c >= n ? 1 : 0;
    else {
        int r, count, mask;
        for (r = count = 0; r < n; r++) {
            mask = 1 << r;
            if ((free & mask) && map[r][c] == '.')
                count += compute_solutions_faster(c + 1,
                        used_rows | mask,
                        (used_up | mask) << 1,
                        (used_down | mask) >> 1);
        }
        return count;
    }
}

/* Main function */
int main() {
    int test = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
        int i, free;
        for (i = 0; i < n; i++)
            assert(scanf(" %s", map[i]) == 1);
        mod = (1 << n) - 1;
        printf("Case %d: %d\n", ++test, 
                compute_solutions_faster(0, 0, 0, 0));
    }
    return EXIT_SUCCESS;
}
