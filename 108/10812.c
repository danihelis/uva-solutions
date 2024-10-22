/* 10812
 * Beat the Spread!
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
    int tests, sum, diff, major, minor;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        assert(scanf("%d %d", &sum, &diff) != EOF);
        major = (sum + diff) / 2;
        minor = sum - major;
        if (minor < 0 || major - minor != diff) {
            printf("impossible\n");
        }
        else {
            printf("%d %d\n", major, minor);
        }
    }
    return 0;
}
