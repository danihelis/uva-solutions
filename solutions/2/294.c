/* 294
 * Divisors
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Calculate the number of divisors */
int num_divisors(int n) {
    int total, k;
    for (total = 1, k = 2; n > 1 && k * k <= n; k += (k == 2 ? 1 : 2)) {
        int count = 0;
        while (n % k == 0) {
            count++;
            n /= k;
        }
        if (count > 0) {
            total += count * total;
        }
    }
    if (k <= n) {
        total *= 2;
    }
    return total;
}

/* Main function */
int main() {
    int i, low, high, best, total, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d %d", &low, &high) != EOF);
        best = low, total = num_divisors(low);
        for (i = low + 1; i <= high; i++) {
            int t = num_divisors(i);
            if (t > total) {
                total = t, best = i;
            }
        }
        printf("Between %d and %d, %d has a maximum of %d divisors.\n",
                low, high, best, total);
    }
    return 0;
}
