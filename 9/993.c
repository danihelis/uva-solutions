/* 993
 * Product of digits
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
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int i, n, count[9];
        assert(scanf("%d", &n) == 1);
        if (n < 10) {
            printf("%d\n", n);
            continue;
        }
        memset(count, 0, 9 * sizeof (int));
        for (i = 9; n > 1 && i >= 2; i--)
            while (n % i == 0)
                count[i - 1]++, n /= i;
        if (n > 1)
            printf("-1\n");
        else {
            for (i = 2; i <= 9; i++)
                for (; count[i - 1] > 0; count[i - 1]--)
                    printf("%d", i);
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
