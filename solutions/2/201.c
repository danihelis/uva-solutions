/* 201
 * Squares
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SQUARES     9
#define MAX_AREA        (MAX_SQUARES * MAX_SQUARES)
#define MAX(x, y)       ((x) > (y) ? (x) : (y))

char horizontal[MAX_SQUARES][MAX_SQUARES], vertical[MAX_SQUARES][MAX_SQUARES];
int dimension, count[MAX_SQUARES];

/* Count all squares */
void count_all() {
    int top, left, i, size, limit, possible;
    memset(count, 0, dimension * sizeof (int));
    for (top = 0; top < dimension - 1; top++) {
        for (left = 0; left < dimension - 1; left++) {
            for (size = 0, limit = dimension - 1 - MAX(top, left); size < limit; size++) {
                if (!horizontal[top][left + size] || !vertical[top + size][left]) {
                    break;
                }
                for (possible = 1, i = left; possible && i <= left + size; i++) {
                    possible &= horizontal[top + size + 1][i];
                }
                for (i = top; possible && i <= top + size; i++) {
                    possible &= vertical[i][left + size + 1];
                }
                count[size] += possible ? 1 : 0;
            }
        }
    }
}

/* Main function */
int main() {
    int num_bars, problem = 0, first = 1;
    while (scanf("%d %d", &dimension, &num_bars) != EOF) {
        int i, x, y;
        (first ? (void) (first = 0) : (void) printf("\n**********************************\n\n"));
        memset(horizontal, 0, MAX_AREA);
        memset(vertical, 0, MAX_AREA);
        for (; num_bars > 0; num_bars--) {
            char type;
            assert(scanf(" %c %d %d", &type, &x, &y) != EOF);
            x--, y--;
            (type == 'H' ? (horizontal[x][y] = 1) : (vertical[y][x] = 1));
        }
        count_all();
        printf("Problem #%d\n\n", ++problem);
        for (i = 0, x = 0; i < dimension; i++) {
            if (count[i] > 0) {
                printf("%d square (s) of size %d\n", count[i], i + 1);
                x = 1;
            }
        }
        if (!x) {
            printf("No completed squares can be found.\n");
        }
    }
    return 0;
}
