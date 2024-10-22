/* 11039
 * Building designing
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_K   999999

/* Main function */
int main() {
    int n;
    assert(scanf("%*d") != EOF);
    while (scanf("%d", &n) == 1) {
        char floor[2][MAX_K];
        int i, value, which, start, height;
        memset(floor, 0, 2 * MAX_K);
        for (i = height = which = 0, start = -1; i < n; i++) {
            assert(scanf("%d", &value) == 1);
            floor[value < 0 ? 0 : 1][abs(value) - 1] = 1;
            if (abs(value) > start)
                start = abs(value) - 1, which = value < 0 ? 0 : 1;
        }
        while (start >= 0) {
            height++, which = 1 - which, --start;
            while (start >= 0 && floor[which][start] == 0)
                start--;
        }
        printf("%d\n", height);
    }
    return EXIT_SUCCESS;
}
