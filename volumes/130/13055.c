/* 13055
 * Inception
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10000
#define MAX_NAME    17

/* Main function */
int main() {
    char stack[MAX_N][MAX_NAME];
    int top = 0, queries;
    assert(scanf("%d", &queries) != EOF);
    while (queries--) {
        char command[MAX_NAME];
        assert(scanf(" %s", command) != EOF);
        if (command[0] == 'S') assert(scanf(" %s", stack[top++]) != EOF);
        else if (command[0] == 'K') (top > 0 ? top-- : (top = 0));
        else printf("%s\n", top > 0 ? stack[top - 1] : "Not in a dream");
    }
    return EXIT_SUCCESS;
}
