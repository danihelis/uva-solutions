/* 839
 * Not so Mobile
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Read input and return whether it is well formed */
int is_mobile_wellformed(int *weight) {
    int wl, dl, wr, dr, wellformed = 1;
    assert(scanf("%d %d %d %d", &wl, &dl, &wr, &dr) == 4);
    if (wl == 0)
        wellformed &= is_mobile_wellformed(&wl);
    if (wr == 0)
        wellformed &= is_mobile_wellformed(&wr);
    wellformed &= wl * dl == wr * dr;
    *weight = wl + wr;
    return wellformed;
}

/* Main function */
int main() {
    int num_tests, dummy;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--)
        printf("%s\n%s", is_mobile_wellformed(&dummy) ? "YES" : "NO",
                num_tests > 1 ? "\n" : "");
    return EXIT_SUCCESS;
}
