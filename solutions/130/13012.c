/* 13012
 * Identifying tea
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define N   5

/* Main function */
int main() {
    int tea, i, ans, count;
    while (scanf("%d", &tea) == 1) {
        for (i = count = 0; i < N; i++) {
            assert(scanf("%d", &ans) == 1);
            count += ans == tea ? 1 : 0;
        }
        printf("%d\n", count);
    }
    return EXIT_SUCCESS;
}
