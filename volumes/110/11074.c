/* 11074
 * Draw Grid
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main function */
int main() {
    int test_case = 0, size, thick, dimension;
    while (scanf("%d %d %d", &size, &thick, &dimension) == 3 && size) {
        int r, c, i, j, width;
        printf("Case %d:\n", ++test_case);
        width = (size + thick) * dimension + thick;
        for (r = 0; r <= dimension; r++) {
            for (i = 0; i < thick; i++) {
                for (j = 0; j < width; j++) {
                    putchar('*');
                }
                putchar('\n');
            }
            if (r == dimension) break;
            for (i = 0; i < size; i++) {
                for (c = 0; c <= dimension; c++) {
                    for (j = 0; j < thick; j++) {
                        putchar('*');
                    }
                    if (c == dimension) break;
                    for (j = 0; j < size; j++) {
                        putchar('.');
                    }
                }
                putchar('\n');
            }
        }
        putchar('\n');
    }
    return EXIT_SUCCESS;
}
