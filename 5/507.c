/* 507
 * Jill Rides Again
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int route, num_routes, num_stops;
    assert(scanf("%d", &num_routes) != EOF);
    for (route = 1; route <= num_routes; route++) {
        int i, best_start = 0, best_end = 0, best_value = 0, start, value, stop;
        assert(scanf("%d", &num_stops) != EOF);
        for (i = 1, start = 1, value = 0; i < num_stops; i++) {
            assert(scanf("%d", &stop) != EOF);
            value += stop;
            if (value > best_value) {
                best_start = start;
                best_end = i + 1;
                best_value = value;
            }
            else if ((value == best_value) && (best_end - best_start < i + 1 - start)) {
                best_start = start;
                best_end = i + 1;
            }
            if (value < 0) {
                start = i + 1;
                value = 0;
            }
        }
        if (best_start == 0) {
            printf("Route %d has no nice parts\n", route);
        }
        else {
            printf("The nicest part of route %d is between stops %d and %d\n", route, best_start,
                    best_end);
        }
    }
    return 0;
}
