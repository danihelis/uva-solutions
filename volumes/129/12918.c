/* 12918
 * Lucky Thief
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
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    while (num_tests-- > 0) {
        long n, m;
        assert(scanf("%ld %ld", &n, &m) != EOF);
        /* (m-1) + (m-2) + ... + (m-n)
         * sum i=1..n { m - i } = m.n - n.(n + 1)/2 
         */
        printf("%ld\n", m * n - n * (n + 1) / 2);
    }
    return EXIT_SUCCESS;
}
