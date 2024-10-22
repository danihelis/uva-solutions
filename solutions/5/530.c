/* 530
 * Binomial Showdown
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MIN(x, y)   ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int n, k, num, den, p;
    long resp;
    while (scanf("%d %d", &n, &k) != EOF && n > 0) {
        p = MIN(k, n - k);
        for (resp = 1, num = n - p + 1, den = 2; num <= n; num++) {
            resp *= num;
            for (; den <= p && resp % den == 0; den++) {
                resp /= den;
            }
        }
        printf("%ld\n", resp);
    }
    return 0;
}
