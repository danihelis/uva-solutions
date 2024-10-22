/* 10678
 * The Grazing Cow
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
    int num_tests;
    double pi = 4 * atan(1);
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int dist, rope;
        double major, minor, area;
        assert(scanf("%d %d", &dist, &rope) != EOF);
        major = rope / 2.0;
        minor = sqrt(major * major - dist * dist / 4.0);
        area = major * minor * pi;
        printf("%.3f\n", area);
    }
    return EXIT_SUCCESS;
}
