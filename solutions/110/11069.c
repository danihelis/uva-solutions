/* 11069
 * A Graph Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   76

/* Main function */
int main() {
    int i, black[MAX_N], sum[MAX_N];
    for (i = 0; i < MAX_N; i++) {
        black[i] = i < 3 ? 1 : black[i - 2] + black[i - 3];
        sum[i] = black[i] + (i < 1 ? 0 : black[i - 1]);
    }
    while (scanf("%d", &i) != EOF)
        printf("%d\n", sum[i - 1]);
    return EXIT_SUCCESS;
}
