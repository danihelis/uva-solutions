/* 10928
 * My Dear Neighbours
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NEIGHBOURS 1000
#define MAX_LINE (10 * MAX_NEIGHBOURS)

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char line[MAX_LINE], *symbol;
        int best[MAX_NEIGHBOURS];
        int i, count, num_neighbours, num_best, minimum;
        assert(scanf("%d", &num_neighbours) != EOF);
        num_best = 0, minimum = 0;
        for (i = 0; i < num_neighbours; i++) {
            assert(scanf(" %[^\n]", line) != EOF);
            count = 0;
            for (symbol = line; *symbol != 0; symbol++) {
                count += (*symbol == ' ' ? 1 : 0);
            }
            if (num_best == 0 || count <  minimum) {
                minimum = count;
                num_best = 1;
                best[0] = i + 1;
            }
            else if (count == minimum) {
                best[num_best++] = i + 1;
            }
        }
        for (i = 0; i < num_best; i++) {
            printf("%d%c", best[i], (i == num_best - 1 ? '\n' : ' '));
        }
    }
    return 0;
}
