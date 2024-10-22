/* 1368
 * DNA Consensus String
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  1010
#define MAX_INPUTS  50
#define INDEX(x)    ((x) == 'A' ? 0 : (x) == 'C' ? 1 : (x) == 'G' ? 2 : 3)
#define CODE(x)     ((x) == 0 ? 'A' : (x) == 1 ? 'C' : (x) == 2 ? 'G' : 'T')

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        char dna[MAX_INPUTS][MAX_STRING];
        int i, n, len, dist;
        assert(scanf("%d %d", &n, &len) == 2);
        for (i = 0; i < n; i++)
            assert(scanf(" %s", dna[i]) == 1);
        for (i = dist = 0; i < len; i++) {
            int k, best, count[4] = {0, 0, 0, 0};
            for (k = 0; k < n; k++)
                count[INDEX(dna[k][i])]++;
            for (best = 0, k = 1; k < 4; k++)
                if (count[k] > count[best])
                    best = k;
            for (k = 0; k < 4; k++)
                if (k != best)
                    dist += count[k];
            printf("%c", CODE(best));
        }
        printf("\n%d\n", dist);
    }
    return EXIT_SUCCESS;
}
