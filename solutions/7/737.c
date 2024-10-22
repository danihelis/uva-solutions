/* 737
 * Gleaming the Cubes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX(x,y)    ((x) > (y) ? (x) : (y))
#define MIN(x,y)    ((x) < (y) ? (x) : (y))
#define MAX_INT     0x7fffffff
#define MIN_INT     0x80000000

typedef int point_t[3];

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int i, d, v;
        point_t i_min, i_max, c_min;
        i_min[0] = i_min[1] = i_min[2] = MIN_INT;
        i_max[0] = i_max[1] = i_max[2] = MAX_INT;
        for (; n > 0; n--) {
            for (i = 0; i < 3; i++) {
                assert(scanf("%d", &c_min[i]) == 1);
                i_min[i] = MAX(i_min[i], c_min[i]);
            }
            assert(scanf("%d", &d) == 1);
            for (i = 0; i < 3; i++)
                i_max[i] = MIN(i_max[i], c_min[i] + d);
        }
        for (i = 0, v = 1; i < 3; i++)
            v *= i_max[i] > i_min[i] ? i_max[i] - i_min[i] : 0;
        printf("%d\n", v);
    }
    return EXIT_SUCCESS;
}
