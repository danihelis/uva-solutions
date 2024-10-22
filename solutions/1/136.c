/* 136
 * Ugly Numbers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIMES  3
#define WHICH_UGLY  1500
#define UGLY_NUMBER 859963392 /* compute_ugly_number(WHICH_UGLY) */

/* Compute k-th ugly number */
int compute_ugly_number(int k) {
    int n, p, i, prime[MAX_PRIMES] = {2, 3, 5};
    for (n = 1; k > 0; n++) {
        for (p = n, i = 0; p > 1 && i < MAX_PRIMES; i++) {
            while (p % prime[i] == 0) {
                p /= prime[i];
            }
        }
        if (p == 1) {
            k--;
        }
    }
    return (n - 1);
}

/* Main function */
int main() {
    printf("The %d'th ugly number is %d.\n", WHICH_UGLY, UGLY_NUMBER);           
    return 0;
}
