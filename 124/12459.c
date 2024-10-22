/* 12459
 * Bees' ancestors
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   80

/* Main function */
int main() {
    long f[MAX_N];
    int i;
    f[0] = 1, f[1] = 2;
    for (i = 2; i < MAX_N; i++)
        f[i] = f[i - 1] + f[i - 2];
    while (scanf("%d", &i) == 1 && i > 0)
        printf("%ld\n", f[--i]);
    return EXIT_SUCCESS;
}
