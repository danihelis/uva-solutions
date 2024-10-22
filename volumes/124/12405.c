/* 12405
 * Scarecrow
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  105

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        int crows, size, i;
        char field[MAX_STRING];
        assert(scanf("%d %s", &size, field) != EOF);
        for (i = crows = 0; i < size; i++)
            if (field[i] == '.')
                crows++, i += 2;
        printf("Case %d: %d\n", test + 1, crows);
    }
    return EXIT_SUCCESS;
}
