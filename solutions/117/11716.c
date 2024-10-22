/* 11716
 * Digital Fortress
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 10002

/* Main function */
#define READ(x) (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    int num_tests;
    char input[MAX_STRING];
    assert(READ(input));
    for (num_tests = atoi(input); num_tests > 0; num_tests--) {
        int length, dim;
        assert(READ(input));
        length = strlen(input) - 1;
        dim = sqrt(length);
        if (dim * dim != length)
            printf("INVALID\n");
        else {
            int i, j, k;
            for (i = 0; i < dim; i++)
                for (j = 0, k = i; j < dim; j++, k += dim)
                    printf("%c", input[k]);
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
