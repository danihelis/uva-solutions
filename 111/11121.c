/* 11121
 * Base -2
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
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int n, last_idx = -1;
        assert(scanf("%d", &n) == 1);
        printf("Case #%d: ", test);
        while (n != 0) {
            int signal = n > 0 ? 1 : -1;
            int idx = n > 0 ? 0 : 1;
            int sum = signal * (1 << idx);
            while (abs(n) > abs(sum)) {
                idx += 2;
                sum += signal * (1 << idx);
            }
            if (last_idx == -1)
                last_idx = idx;
            else
                for (last_idx--; last_idx > idx; last_idx--)
                    putchar('0');
            putchar('1');
            n -= signal * (1 << idx);
        }
        if (last_idx == -1)
            last_idx = 1; /* input was zero */
        for (; last_idx > 0; last_idx--)
            putchar('0');
        puts("");
    }
    return EXIT_SUCCESS;
}
