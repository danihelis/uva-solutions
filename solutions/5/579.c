/* 579
 * Clock Hands
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define HOUR_DEGREE         30      /* (360 / 12) */
#define HOUR_MINUTE_DEGREE  0.5     /*(HOUR_DEGREE / 60.0) */
#define MINUTE_DEGREE       6       /* (360 / 60) */

#define FULL_CIRCLE         360
#define HALF_CIRCLE         180     /* (FULL_CIRCLE / 2) */

#define ABS_DIFF(x, y)      ((x) > (y) ? (x) - (y) : (y) - (x))
#define EPSILON             1e-4

/* Main function */
int main() {
    int hour, minute;
    while (scanf("%d:%d", &hour, &minute) != EOF && hour > 0) {
        double degree = ABS_DIFF(HOUR_DEGREE * hour + HOUR_MINUTE_DEGREE * minute, 
                MINUTE_DEGREE * minute);
        if ((degree - HALF_CIRCLE) > -EPSILON) {
            degree = FULL_CIRCLE - degree;
        }
        printf("%.3f\n", degree);
    }
    return 0;
}
