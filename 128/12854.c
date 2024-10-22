/* 12854
 * Automated Checking Machine
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define N 5

/* Main function */
int main() {
    while (!feof(stdin)) {
        int i, p[N], v, valid;
        for (i = 0; i < N; i++)
            assert(scanf("%d", &p[i]) == 1);
        for (i = 0, valid = 1; i < N; i++) {
            assert(scanf("%d ", &v) == 1);
            valid &= v != p[i];
        }
        printf("%c\n", valid ? 'Y' : 'N');
    }
    return EXIT_SUCCESS;
}
