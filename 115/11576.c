/* 11576
 * Scrolling Sign
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LETTERS     100
#define MAX_STRING      (MAX_LETTERS + 2)

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int n, k, m, total;
        char sign[MAX_STRING], input[MAX_STRING], *s;
        assert(scanf("%d %d %s", &k, &n, sign) != EOF);
        for (n--, total = k; n > 0; n--) {
            assert(scanf(" %s", input) != EOF);
            for (s = sign, m = k; m > 0 && strncmp(s, input, m) != 0; 
                    s++, total++, m--)
                ;
            strcpy(sign, input);
        }
        printf("%d\n", total);
    }
    return EXIT_SUCCESS;
}
