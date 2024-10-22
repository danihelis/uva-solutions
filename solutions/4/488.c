/* 488
 * Triangle Wave
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
    int ampl, freq, num_tests, first = 1, first_wave, height, i, j;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        (first ? (void) (first = 0) : (void) printf("\n"));
        assert(scanf("%d %d", &ampl, &freq) != EOF);
        for (first_wave = 1; freq > 0; freq--) {
            (first_wave ? (void) (first_wave = 0) : (void) printf("\n"));
            for (i = 1; i < ampl * 2; i++) {
                for (height = (i > ampl ? 2 * ampl - i : i), j = 0; j < height; j++) {
                    printf("%d", height);
                }
                printf("\n");
            }
        }
    }
    return 0;
}
