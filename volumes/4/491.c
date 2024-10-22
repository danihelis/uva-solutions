/* 491
 * Tile Topology
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_RESP    16

int resp[MAX_RESP] = {
    0, 1, 1, 2, 7, 18,
    60, 196, 704, 2500, 9189,
    33896, 126759, 476270, 1802312, 6849777};

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        assert(n < MAX_RESP);
        printf("%d\n", resp[n]);
    }
    return 0;
}
