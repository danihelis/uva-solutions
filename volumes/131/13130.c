/* 13130
 * Cacho
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        int i, dice[5], scale;
        for (i = 0, scale = 1; i < 5; i++) {
            assert(scanf("%d", &dice[i]) == 1);
            if (i > 0) scale &= dice[i] == dice[i - 1] + 1;
        }
        printf("%c\n", scale ? 'Y' : 'N');
    }
    return EXIT_SUCCESS;
}
