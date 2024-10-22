/* 11044
 * Searching for Nessy
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
    int width, height, tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        assert(scanf("%d %d", &width, &height) != EOF);
        printf("%d\n", (int) (width / 3) * (int) (height / 3));
    }
    return 0;
}
