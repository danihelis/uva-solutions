/* 232
 * Crossword Answers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIM     10
#define MAX_STRING  (MAX_DIM + 2)

/* Main function */
int main() {
    char grid[MAX_DIM][MAX_STRING];
    int number[MAX_DIM][MAX_DIM], count;
    int puzzle = 0, first = 1, rows, cols, i, j, k, c;
    while (scanf("%d %d", &rows, &cols) != EOF && rows > 0) {
        for (i = 0; i < rows; i++) {
            assert(scanf(" %s", grid[i]) != EOF);
        }
        for (i = 0, count = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                number[i][j] = grid[i][j] != '*' && (i == 0 || j == 0 || grid[i - 1][j] == '*' || 
                        grid[i][j - 1] == '*') ? ++count : 0;
            }
        }
        (first ? (first = 0) : printf("\n"));
        printf("puzzle #%d:\n", ++puzzle);
        for (k = 0; k < 2; k++) {
            printf("%s\n", k == 0 ? "Across" : "Down");
            for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                    if (number[i][j] > 0 && ((k == 0 && (j == 0 || grid[i][j - 1] == '*')) ||
                                (k == 1 && (i == 0 || grid[i - 1][j] == '*')))) {
                        printf("%3d.", number[i][j]);
                        if (k == 0) {
                            for (c = j; c < cols && grid[i][c] != '*'; c++) {
                                printf("%c", grid[i][c]);
                            }
                        }
                        else {
                            for (c = i; c < rows && grid[c][j] != '*'; c++) {
                                printf("%c", grid[c][j]);
                            }
                        }
                        printf("\n");
                    }
                }
            }
        }
    }
    return 0;
}
