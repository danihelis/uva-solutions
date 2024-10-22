/* 12578
 * 10:6:2
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
    double pi = acos(-1);
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int width;
        double height, radius, circle, area;
        assert(scanf("%d", &width) != EOF);
        height = width * 6.0 / 10.0;
        radius = width * 2.0 / 10.0;
        area = height * width;
        circle = radius * radius * pi;
        area -= circle;
        printf("%.2f %.2f\n", circle, area);
    }
    return EXIT_SUCCESS;
}
