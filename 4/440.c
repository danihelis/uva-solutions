/* 440
 * Eeny Meeny Moo
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Check whether a Josephus cycle (n,m) can end on the 2nd element */
int feasible_cycle(int n, int m) {
    int index = 0, size = n - 1;
    while (size > 1) {
        index = (index + size - 1) % size;
        index = (index + m) % size;
        if (index == 0)
            return 0;
        size--;
    }
    return 1;
}

/* Main function */
int main() {
    int n, m;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (m = 2; !feasible_cycle(n, m); m++)
            ;
        printf("%d\n", m);
    }
    return EXIT_SUCCESS;
}
