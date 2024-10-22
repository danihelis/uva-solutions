/* 12024
 * Hats
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Solution for n,
 *        n                                 n
 *      Sum  C(n,i) · i! · (-1)^(i+n)  =  Sum  n! / (n-i)! · (-1)^(i+n)
 *       i=0                               i=0
 *
 * Simplifying,     
 *      n!/2! - n!/3! + ... ± n ± 1
 */

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int i, n, fat, ans;
        assert(scanf("%d", &n) == 1);
        for (fat = 1, i = 2; i <= n; fat *= i++)
            ;
        for (ans = 0, n = fat, i = 2; n > 1; i++) {
            ans += (n / i) * (i % 2 == 0 ? 1 : -1);
            n /= i;
        }
        printf("%d/%d\n", ans, fat);
    }
    return EXIT_SUCCESS;
}
