/* 10656
 * Maximum Sum (II)
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
    int n, i, v, first;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (i = 0, first = 1; i < n; i++) {
            assert(scanf("%d", &v) != EOF);
            if (v > 0) {
                (first ? (first = 0) : printf(" "));
                printf("%d", v);
            }

        }
        printf("%s\n", first ? "0" : "");
    }
    return EXIT_SUCCESS;
}
