/* 10991
 * Region
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        double r[3], s[3], half_sum, sq_sum, prod, area;
        int i;
        for (i = 0, half_sum = 0; i < 3; i++) {
            assert(scanf("%lf", &r[i]) == 1);
            half_sum += r[i]; /* sum of sides div 2 */
        }
        for (i = 0, area = half_sum, sq_sum = 0, prod = 1; i < 3; i++) {
            s[i] = half_sum - r[i]; /* opposite side */
            sq_sum += s[i] * s[i]; /* sum of side squares */
            prod *= s[i]; /* product of sides */
            area *= half_sum - s[i];
        }
        area = sqrt(area); /* triangle area: sqrt(s·(s-a)·(s-b)·(s-c)) */
        for (i = 0; i < 3; i++) {
            /* arc angle: arccos((b² + c² - a²) / 2·b·c)
             * arc area: angle · r² / 2 */
            double a = (sq_sum - 2 * s[i] * s[i]) / (2 * prod / s[i]);
            area -= acos(a) * r[i] * r[i] / 2;
        }
        printf("%.6f\n", area);
    }
    return EXIT_SUCCESS;
}
