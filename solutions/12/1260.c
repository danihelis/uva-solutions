/* 1260
 * Sales
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   1000

/* Main function */
int main() {
    int tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        int a[MAX_N], n, b, i, j;
        assert(scanf("%d", &n) != EOF);
        for (i = 0, b = 0; i < n; i++) {
            assert(scanf("%d", &a[i]) != EOF);
            for (j = 0; j < i; j++) {
                if (a[j] <= a[i])
                    b++;
            }
        }
        printf("%d\n", b);
    }
    return EXIT_SUCCESS;
}
