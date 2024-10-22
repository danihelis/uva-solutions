/* 12015
 * Google is Feeling Lucky
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_ENTRIES     10
#define MAX_STRING      102

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        char url[NUM_ENTRIES][MAX_STRING], input[MAX_STRING];
        int i, best, size, value;
        for (i = 0, best = -1, size = 0; i < NUM_ENTRIES; i++) {
            assert(scanf(" %s %d", input, &value));
            if (size == 0 || value > best)
                best = value, size = 0;
            if (value == best)
                strcpy(url[size++], input);
        }
        printf("Case #%d:\n", test);
        for (i = 0; i < size; i++)
            printf("%s\n", url[i]);
    }
    return EXIT_SUCCESS;
}
