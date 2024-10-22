/* 382
 * Perfection
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

int perfection(int n) {
    int sum, k;
    for (sum = 1, k = 2; k <= (n >> 1); k++) {
        if (n % k == 0) {
            sum += k;
            if (sum > n) {
                return 1;
            }
        }
    }
    return (sum == n && n != 1 ? 0 : -1);
}

/* Main function */
int main() {
    int p, n;
    printf("PERFECTION OUTPUT\n");
    while (scanf("%d", &n) != EOF && n > 0) {
        p = perfection(n);
        printf("%5d  %s\n", n, (p == 0 ? "PERFECT" : p < 0 ? "DEFICIENT" : "ABUNDANT"));
    }
    printf("END OF OUTPUT\n");
    return 0;
}
