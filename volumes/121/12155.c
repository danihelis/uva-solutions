/* 12155
 * ASCII Diamondi
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define LETTERS 26

/* Main function */
int main() {
    int n, row1, row2, col1, col2, test = 0;
    while (scanf("%d %d %d %d %d", &n, &row1, &col1, &row2, &col2) != EOF && n > 0) {
        int row, col, r, c, dim;
        printf("Case %d:\n", ++test);
        dim = 2 * n - 1;
        for (row = row1; row <= row2; row++) {
            r = row % dim;
            r = r < n ? r + 1 : dim - r;
            for (col = col1; col <= col2; col++) {
                c = col % dim;
                c = c < n ? c + 1: dim - c;
                if (r + c <= n) {
                    printf(".");
                }
                else {
                    char symb = ((2 * n - r - c) % LETTERS) + 'a';
                    printf("%c", symb);
                }                                                
            }
            printf("\n");
        }
    }
    return 0;
}
