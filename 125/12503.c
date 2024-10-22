/* 12503
 * Robot Instructions
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define MAX_STRING  20

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char inst[MAX_N];
        int i, n, v, pos;
        assert(scanf("%d", &n) != EOF);
        for (pos = 0, i = 0; i < n; i++) {
            assert(scanf(" %c%*s", &inst[i]) != EOF);
            if (inst[i] == 'S') {
                assert(scanf(" %*s %d", &v) != EOF);
                inst[i] = inst[--v];
            }
            pos += inst[i] == 'L' ? -1 : 1;
        }
        printf("%d\n", pos);
    }
    return EXIT_SUCCESS;
}
