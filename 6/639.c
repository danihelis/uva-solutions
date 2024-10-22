/* 639
 * Don't Get Rooked
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIMENSION   4
#define FREE            '.'
#define BLOCKED         'X'
#define USED            'a'

#define SET_LEVEL(var,r,c,is_row,in,new) do { \
        int v; \
        for (v = var + 1; v < dimension; v++) { \
            char *pos = (is_row ? &table[v][c] : &table[r][v]); \
            if (*pos == in) \
                *pos = new; \
            else if (*pos == BLOCKED) \
                break; \
        } \
    } while (0)

char table[MAX_DIMENSION][MAX_DIMENSION + 2];
int dimension;

/* Try to place as many rooks as possible */
int place_rooks(int row, int column, char level) {
    int sum, best_sum, i, j;
    for (i = row, best_sum = 0; i < dimension; i++) {
        for (j = (i == row ? column : 0); j < dimension; j++) {
            if (table[i][j] == FREE) {
                SET_LEVEL(i, i, j, 1, FREE, level);
                SET_LEVEL(j, i, j, 0, FREE, level);
                sum = 1 + place_rooks(i, j + 1, level + 1);
                if (sum > best_sum) {
                    best_sum = sum;
                }
                SET_LEVEL(i, i, j, 1, level, FREE);
                SET_LEVEL(j, i, j, 0, level, FREE);
            }
        }
    }
    return best_sum;
}

/* Main function */
int main() {
    while (scanf("%d", &dimension) != EOF && dimension > 0) {
        int i;
        for (i = 0; i < dimension; i++) {
            assert(scanf(" %s", table[i]) != EOF);
        }
        printf("%d\n", place_rooks(0, 0, USED));
    }
    return 0;
}
