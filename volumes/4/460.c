/* 460
 * Overlapping Rectangles
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        /* [window][point][coord] */
        int point[2][2][2], ipoint[2][2];
        int w, p, c, invalid;
        for (w = 0; w < 2; w++)
            for (p = 0; p < 2; p++)
                for (c = 0; c < 2; c++)
                    assert(scanf("%d", &point[w][p][c]) != EOF);
        for (p = 0; p < 2; p++)
            for (c = 0; c < 2; c++)
                ipoint[p][c] = p == 0 ? 
                        MAX(point[0][p][c], point[1][p][c]) :
                        MIN(point[0][p][c], point[1][p][c]);
        for (c = 0, invalid = 0; c < 2; c++)
            invalid |= ipoint[1][c] - ipoint[0][c] <= 0;
        if (invalid)
            printf("No Overlap");
        else
            for (p = 0; p < 2; p++)
                for (c = 0; c < 2; c++)
                    printf("%s%d", p == 0 && c == 0 ? "" : " ", 
                            ipoint[p][c]);
        printf("\n%s", num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
