/* 10235
 * Simply Emirp
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Is prime? */
int is_prime(int n) {
    int k;
    if (n <= 1 || n % 2 == 0) {
        return 0;
    }
    for (k = 3; k * k <= n; k += 2) {
        if (n % k == 0) {
            return 0;
        }
    }
    return 1;
}

/* Reverse the digits of a number */
int reverse(int n) {
    int r = 0;
    while (n > 0) {
        r *= 10;
        r += n % 10;
        n /= 10;
    }
    return r;
}

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int r;
        printf("%d is %s.\n", n, (is_prime(n) ? 
                    ((r = reverse(n)) != n && is_prime(r)) ? "emirp" : "prime" : "not prime"));
    }
    return 0;
}
