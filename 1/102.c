/* 102
 * Ecological Bin Packing
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_COMB        6
#define NUM_BINS        3
#define NUM_GLASSES     3
#define GET_GLASS(x)    (x == 'B' ? 0 : x == 'G' ? 1 : 2)

char *comb[NUM_COMB] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};

/* Main function */
int main() {
    int bin[NUM_BINS][NUM_GLASSES], total[NUM_GLASSES];
    while (scanf("%d", &bin[0][0]) != EOF) {
        int i, b, g, best, minimum;
        memset(total, 0, NUM_GLASSES * sizeof (int));
        for (b = 0; b < NUM_BINS; b++) {
            for (g = 0; g < NUM_GLASSES; g++) {
                if (b > 0 || g > 0) {
                    assert(scanf("%d", &bin[b][g]) != EOF);
                }
                total[g] += bin[b][g];
            }
        }
        for (i = 0, best = -1, minimum = -1; i < NUM_COMB; i++) {
            int exchange = 0;
            char *seq = comb[i];
            for (b = 0; b < NUM_BINS; b++) {
                exchange += total[GET_GLASS(seq[b])] - bin[b][GET_GLASS(seq[b])];
            }
            if (best == -1 || exchange < minimum) {
                best = i;
                minimum = exchange;
            }
        }
        printf("%s %d\n", comb[best], minimum);
    }
    return 0;
}
