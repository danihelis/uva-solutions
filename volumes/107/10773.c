/* 10773
 * Back to Intermediate Math
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define EPSILON     1e-5

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        double dist, river, boat, fastest, shortest;
        assert(scanf("%lf %lf %lf", &dist, &river, &boat) != EOF);
        printf("Case %d: ", test + 1);
        if (river < EPSILON || boat <= river) {
            printf("can't determine\n");
            continue;
        }
        fastest = dist / boat;
        shortest = dist / sqrt(boat * boat - river * river);
        printf("%.3f\n", shortest - fastest);
    }
    return EXIT_SUCCESS;
}
