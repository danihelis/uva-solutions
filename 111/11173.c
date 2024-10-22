/* 11173
 * Grey Codes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#if 0
/* Old main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int b, i;
        long n, answer;
        assert(scanf("%d %ld", &b, &n) == 2);
        for (answer = i = 0; n > 0; i++, n >>= 1) {
            char bit = n & 2 ? 1 - (n & 1) : n & 1;
            if (bit)
                answer |= 1 << i;
        }
        printf("%ld\n", answer);
    }     
    return EXIT_SUCCESS;
}
#endif

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        int n;
        assert(scanf("%*d %d", &n) == 1);
        printf("%d\n", n ^ (n >> 1));
    }     
    return EXIT_SUCCESS;
}
