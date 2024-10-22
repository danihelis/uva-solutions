/* 11586
 * Train Tracks
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
    assert(scanf("%d ", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int unpaired_males = 0, pieces = 0;
        char p1, p2, end;
        do {
            assert(scanf(" %c%c%c", &p1, &p2, &end) == 3);
            if (p1 == p2)
                unpaired_males += (p1 == 'M' ? 1 : -1);
            pieces++;
        } while (end != '\n');
        printf("%sLOOP\n", unpaired_males == 0 && pieces > 1 ? "" : "NO ");
    }
    return EXIT_SUCCESS;
}
