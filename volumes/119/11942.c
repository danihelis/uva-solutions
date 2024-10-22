/* 11942
 * Lumberjack Sequencing
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
    assert(scanf("%d", &num_tests) != EOF);
    printf("Lumberjacks:\n");
    for (; num_tests > 0; num_tests--) {
        int i, k, ordered, value, last;
        for (i = k = 0, ordered = 1, last = -1; i < 10; i++) {
            assert(scanf("%d", &value) != EOF);
            if (i > 0) {
                if (k == 0)
                    k = value - last;
                else
                    ordered &= k < 0 ? value <= last : last <= value;
            }
            last = value;
        }
        printf("%s\n", ordered ? "Ordered" : "Unordered");
    }
    return EXIT_SUCCESS;
}
