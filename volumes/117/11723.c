/* 11723
 * Numbering Roads
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
    int n, r, value, test = 0;
    while (scanf("%d %d", &n, &r) != EOF && n > 0) {
        value = (n - 1) / r;
        printf("Case %d: ", ++test);
        (value > 26 ? printf("impossible\n") : printf("%d\n", value));
    }
    return EXIT_SUCCESS;
}
