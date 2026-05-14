/* 11313
 * Gourmet Games
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
    int num_tests, n, m, k;
    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        assert(scanf("%d %d", &n, &m) == 2);
        k = 0;
        while (n >= m) {
            k++;
            n -= m - 1;
        }
        if (n == 1) printf("%d\n", k);
        else printf("cannot do this\n");
    }
    return EXIT_SUCCESS;
}
