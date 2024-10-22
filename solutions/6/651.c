/* 651
 * Deck
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100000

/* Main function */
int main() {
    double len[MAX_N];
    int n;
    for (n = 1, len[0] = 0; n < MAX_N; n++)
        len[n] = len[n - 1] + 0.5 / (double) n;
    printf("# Cards Overhang\n");
    while (scanf("%d", &n) != EOF)
        printf("%5d%10.3f\n", n, len[n]);
    return EXIT_SUCCESS;
}
