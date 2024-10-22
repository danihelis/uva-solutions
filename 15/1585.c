/* 1585
 * Score
 * by Daniel Donadon
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_STRING  100

int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char string[MAX_STRING], *c;
        int sum, count;
        assert(scanf(" %s", string) != EOF);
        for (sum = count = 0, c = string; *c != 0; c++)
            if (*c == 'X')
                count = 0;
            else
                sum += ++count;
        printf("%d\n", sum);
    }
    return EXIT_SUCCESS;
}
