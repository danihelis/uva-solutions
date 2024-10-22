/* 1062
 * Containers
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STACKS  26
#define MAX_STRING  1002

/* Main function */
int main() {
    char *i, input[MAX_STRING], stack[MAX_STACKS];
    int num_stacks, s, found, test;
    test = 0;
    while (scanf(" %s", input) != EOF && input[0] != 'e') {
        num_stacks = 0;
        for (i = input; *i != 0; i++) {
            for (s = 0, found = 0; !found && s < num_stacks; s++) {
                if (*i <= stack[s]) {
                    found = 1;
                    stack[s] = *i;
                }
            }
            if (!found) {
                stack[num_stacks++] = *i;
            }
        }
        printf("Case %d: %d\n", ++test, num_stacks);
    }
    return 0;
}
