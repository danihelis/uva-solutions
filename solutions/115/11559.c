/* 11559
 * Event Planning
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_HOTELS  20

/* Main function */
int main() {
    int num_parts, budget, num_hotels, num_weeks;
    while (scanf("%d %d %d %d", &num_parts, &budget, &num_hotels, &num_weeks) != EOF) {
        int i, w, beds, possible, cost, lowest;
        for (i = 0, lowest = -1; i < num_hotels; i++) {
            assert(scanf("%d", &cost) != EOF);
            cost *= num_parts;
            for (w = 0, possible = 0; w < num_weeks; w++) {
                assert(scanf("%d", &beds) != EOF);
                possible |= beds >= num_parts;
            }
            if (possible && cost <= budget && (lowest < 0 || cost < lowest)) {
                lowest = cost;
            }
        }
        (lowest < 0 ? printf("stay home\n") : printf("%d\n", lowest));
    }
    return 0;
}
