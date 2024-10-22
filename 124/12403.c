/* 12403
 * Save Setu
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
    int n, k, v;
    char op;
    assert(scanf("%d", &n) != EOF);
    for (k = 0; n > 0; n--) {
        assert(scanf(" %c%*s", &op) != EOF);
        if (op == 'd') {
            assert(scanf("%d", &v) != EOF);
            k += v;
        }
        else 
            printf("%d\n", k);
    }
    return EXIT_SUCCESS;
}
