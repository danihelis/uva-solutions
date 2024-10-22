/* 11258
 * String Partition
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DIGITS  200

long MAX_VALUE = ((1L << 31) - 1);

/* Compute best sum */
long compute_best_sum(char *digits) {
    long best_sum[MAX_DIGITS + 1];
    int i, p, n = strlen(digits);
    best_sum[n] = 0L;
    for (p = n - 1; p >= 0; p--) {
        long prefix, sum;
        if (digits[p] == '0')
            best_sum[p] = best_sum[p + 1];
        else
            for (prefix = 0L, best_sum[p] = 0L, i = p; i < n; i++) {
                prefix = prefix * 10 + (digits[i] - '0');
                if (prefix > MAX_VALUE)
                    break;
                sum = prefix + best_sum[i + 1];
                if (sum > best_sum[p])
                    best_sum[p] = sum;
            }
    }
    return best_sum[0];
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char number[MAX_DIGITS + 2];
        assert(scanf(" %s", number) != EOF);
        printf("%ld\n", compute_best_sum(number));
    } 
    return EXIT_SUCCESS;
}
