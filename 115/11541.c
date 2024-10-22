/* 11541
 * Decoding
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 500

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        char *i, input[MAX_STRING];
        assert(scanf(" %s", input) != EOF);
        printf("Case %d: ", test);
        i = input; 
        while (*i != 0) {
            char symbol = *(i++);
            int repeat = 0;
            for (repeat = 0; isdigit(*i); i++)
                repeat = repeat * 10 + *i - '0';
            for (; repeat > 0; repeat--)
                printf("%c", symbol);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
