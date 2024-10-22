/* 12955
 * Factorial
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_VALUE   100000
#define MAX_N       10

/* Main function */
int main() {
    int fatorial[MAX_N];
    int i, n, total, num_fatorials;
    for (fatorial[0] = 1, i = 1; fatorial[i - 1] < MAX_VALUE; i++) {
        fatorial[i] = fatorial[i - 1] * (i + 1);
    }
    num_fatorials = i;
    while (scanf("%d", &n) != EOF) {
        total = 0;
        while (n > 0) {
            for (i = 0; i < num_fatorials && fatorial[i] <= n; i++)
                ;
            total += n / fatorial[i - 1];
            n %= fatorial[i - 1];
        }
        printf("%d\n", total);
    }
    return EXIT_SUCCESS;
}
