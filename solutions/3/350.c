/* 350
 * Pseudo-Random Numbers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CYCLE   10000

int cycle[MAX_CYCLE];

/* Main function */
int main() {
    int z, i, m, v, c, test = 0;
    while (scanf("%d %d %d %d", &z, &i, &m, &v) != EOF && m > 0) {
        memset(cycle, 0, sizeof (int) * m);
        for (c = 1; cycle[v] == 0; c++) {
            cycle[v] = c;
            v = (z * v + i) % m;
        }
        printf("Case %d: %d\n", ++test, c - cycle[v]);
    }
    return 0;
}
