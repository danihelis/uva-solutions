/* 11650
 * Mirror Clock
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
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int hour, minute;
        assert(scanf("%d:%d", &hour, &minute) == 2);
        minute = (60 - minute) % 60;
        hour = 12 - hour % 12 - (minute > 0 ? 1 : 0);
        if (hour == 0)
            hour = 12;
        printf("%02d:%02d\n", hour, minute);
    }
    return EXIT_SUCCESS;
}
