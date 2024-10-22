/* 12279
 * Emoogle Balance
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int test = 0, n, value, balance;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (balance = 0; n > 0; n--) {
            assert(scanf("%d", &value) != EOF);
            balance += value > 0 ? 1 : -1;
        }
        printf("Case %d: %d\n", ++test, balance);
    }
    return EXIT_SUCCESS;
}
