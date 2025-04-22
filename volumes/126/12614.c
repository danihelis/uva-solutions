/* 12614
 * Earn For Future
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main function */
int main() {
    int test, num_tests, cards, value, max;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        assert(scanf("%d", &cards) == 1);
        max = 0;
        while (cards-- > 0) {
            assert(scanf("%d", &value) == 1);
            max = value > max ? value : max;
        }
        printf("Case %d: %d\n", test, max);
    }
    return EXIT_SUCCESS;
}
