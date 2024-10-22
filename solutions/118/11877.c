/* 11877
 * The Coco-Cola Store
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100

/* Main function */
int main() {
    int n, coca[MAX_N + 1];
    coca[0] = 0, coca[1] = 0, coca[2] = 1;
    for (n = 3; n <= MAX_N; n++) {
        int bottles = n - 2 * (n / 3);
        coca[n] = n / 3 + coca[bottles];
    }
    while (scanf("%d", &n) != EOF && n > 0)
        printf("%d\n", coca[n]);
    return EXIT_SUCCESS;
}
