/* 11054
 * Wine trading in Gergovia
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int i, num_houses, wine;
    long long demand, cost;
    while (scanf("%d", &num_houses) != EOF && num_houses > 0) {
        for (i = 0, demand = 0, cost = 0; i < num_houses; i++) {
            assert(scanf("%d", &wine) != EOF);
            cost += (demand < 0 ? -demand : demand);
            demand += wine;
        }
        assert(demand == 0);
        printf("%lld\n", cost);
    }
    return 0;
}
