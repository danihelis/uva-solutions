/* 12455
 * Bars
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BARS    20

int length[MAX_BARS], num_bars;

/* Whether one can compose a bar of a given size */
int can_compose(int index, int size) {
    if (size == 0)
        return 1;
    if (index >= num_bars)
        return 0;
    if (length[index] <= size && 
            can_compose(index + 1, size - length[index]))
        return 1;
    return can_compose(index + 1, size);
}

/* Main function */
int main() {
    int i, size, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d %d", &size, &num_bars) != EOF);
        for (i = 0; i < num_bars; i++)
            assert(scanf("%d", &length[i]) != EOF);
        printf("%s\n", can_compose(0, size) ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}
