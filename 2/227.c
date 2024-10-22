/* 227
 * Puzzle
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define DIM 5

char puzzle[DIM][DIM];
int row, col;

/* Main function */
int main() {
    int test = 0;
    char input, valid;

    while ((input = getchar()) != 'Z') {
        int i, j;
        row = col = i = j = 0;
        do {
            if (input != '\n') {
                if (input == ' ')
                    row = i, col = j;
                puzzle[i][j++] = input;
            } else
                i++, j = 0;
            input = getchar();
        } while (i < DIM);
        for (valid = 1; input != '0'; input = getchar()) 
            if (valid && input != '\n') {
                int sr = row, sc = col;
                switch (input) {
                    case 'A': sr--; break;
                    case 'B': sr++; break;
                    case 'L': sc--; break;
                    case 'R': sc++; break;
                    default:
                              valid = 0;
                }
                if (sr < 0 || sr >= DIM || sc < 0 || sc >= DIM)
                    valid = 0;
                else {
                    puzzle[row][col] = puzzle[sr][sc];
                    puzzle[sr][sc] = ' ';
                    row = sr, col = sc;
                }
            }
        assert((input = getchar()) == '\n');
        if (test > 0)
            puts("");
        printf("Puzzle #%d:\n", ++test);
        if (!valid)
            puts("This puzzle has no final configuration.");
        else {
            for (i = 0; i < DIM; i++)
                for (j = 0; j < DIM; j++)
                    printf("%c%c", puzzle[i][j], j == DIM - 1 ? '\n' : ' ');
        }
    }

    return EXIT_SUCCESS;
}
