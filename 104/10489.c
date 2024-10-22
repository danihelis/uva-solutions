/* 10489
 * Boxes of Chocolates
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
        int n, b, k, a, boxes, total = 0;
        assert(scanf("%d %d", &n, &b) != EOF);
        while (b-- > 0) {
            assert(scanf("%d", &k) != EOF);
            for (boxes = 1; k > 0; k--) {
                assert(scanf("%d", &a) != EOF);
                boxes = (boxes * a) % n;
            }
            total = (total + boxes) % n;
        }
        printf("%d\n", total);
    }
    return EXIT_SUCCESS;
}
