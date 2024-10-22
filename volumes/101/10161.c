/* 10161
 * Ant on a Chessboard
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SQ(x)   ((x) * (x))
#define ABS(x)  ((x) >= 0 ? (x) : - (x));

/* Main function */
int main() {
    int t, n, m, d;
    while (scanf("%d", &t) != EOF && t > 0) {
        n = ceil(sqrt(t));
        m = SQ(n) - n + 1;
        d = ABS(m - t);
        if ((t < m) ^ (n % 2)) {
            printf("%d %d\n", n - d, n);
        }
        else {
            printf("%d %d\n", n, n - d);
        }
    }
    return 0;
}
