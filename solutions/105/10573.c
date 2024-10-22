/* 10573
 * Geometry Paradox
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LINE    100
#define READ(x)     (fgets(x, MAX_LINE, stdin) != NULL)

/* Main function */
int main() {
    char line[MAX_LINE];
    int tests;
    double pi;
    pi = acos(0) * 2;
    assert(READ(line));
    for (tests = atoi(line); tests > 0; tests--) {
        int a, b;
        double res;
        assert(READ(line));
        if (sscanf(line, "%d %d", &a, &b) == 1)
            res = pi * a * a / 8;
        else
            res = pi * a * b * 2;
        printf("%.4f\n", res);
    }
    return EXIT_SUCCESS;
}
