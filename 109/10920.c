/* 10920
 * Spiral Tap
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    long size, pos;
    while (scanf("%ld %ld", &size, &pos) != EOF && size > 0) {
        long row, col, half, n, corner;
        int i;
        col = row = size / 2 + 1;
        n = ceil(sqrt(pos));
        if (n % 2 == 0) {
            n++;
        }
        corner = n * n;
        half = n / 2;
        for (i = 0; i < 4; i++) {
            if (pos >= corner - n + 1) {
                col += i % 2 == 0 ? half * (1 - i) :
                        (pos - corner + half) * (2 - i);
                row += i % 2 == 1 ? half * (i - 2) :
                        (pos - corner + half) * (1 - i);
                break;
            }
            corner -= n - 1;
        }
        printf("Line = %ld, column = %ld.\n", row, col);
    }
    return 0;
}
