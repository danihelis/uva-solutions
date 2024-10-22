/* 957
 * Popes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_POPES   100000

/* Main function */
int main() {
    int year[MAX_POPES];
    int period, num_popes;
    while (scanf("%d %d", &period, &num_popes) != EOF) {
        int i, start, sum, best_sum, best_start = -1, best_end = -1;
        for (i = 0, best_sum = 0, sum = 0, start = 0; i < num_popes; i++) {
            assert(scanf("%d", &year[i]) != EOF);
            sum++;
            for (; year[i] - year[start] >= period; start++) {
                sum--;
            }
            if (sum > best_sum) {
                best_sum = sum;
                best_start = start;
                best_end = i;
            }
        }
        assert(best_start != -1 && best_end != -1);
        printf("%d %d %d\n", best_sum, year[best_start], year[best_end]);
    }

    return 0;
}
