/* 10116
 * Robot Motion
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     10
#define MAX_STRING  (MAX_DIM + 2)
#define IN(x,v)     ((x) >= 0 && (x) < (v))
#define INSIDE(r,c) (IN(r,rows) && IN(c,cols))

char map[MAX_DIM][MAX_STRING];
int step[MAX_DIM][MAX_STRING];
int rows, cols;

/* Main function */
int main() {
    int row, col;
    while (scanf("%d %d %d", &rows, &cols, &col) == 3 && rows > 0) {
        int i, count;
        for (i = 0; i < rows; i++) {
            assert(scanf(" %s", map[i]) == 1);
            memset(step[i], 0, cols * sizeof (int));
        }
        count = 0, row = 0, col--;
        while (INSIDE(row, col) && step[row][col] == 0) {
            step[row][col] = ++count;
            switch (map[row][col]) {
                case 'N': row--; break;
                case 'S': row++; break;
                case 'W': col--; break;
                case 'E': col++; break;
            }
        }
        if (INSIDE(row, col))
            printf("%d step(s) before a loop of %d step(s)\n",
                    step[row][col] - 1, count - step[row][col] + 1);
        else
            printf("%d step(s) to exit\n", count);
    }
    return EXIT_SUCCESS;
}
