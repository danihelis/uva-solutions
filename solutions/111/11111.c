/* 11111
 * Generalized Matrioshkas
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STACK   100000
#define MAX_LINE    (MAX_STACK * 8)

/* Main function */
int main() {
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        int valid, top, stack[MAX_STACK];
        char *s;
        for (s = strtok(line, " \n"), valid = 1, top = 0; valid && s != NULL;
                s = strtok(NULL, " \n")) {
            int value = atoi(s);
            if (value < 0)
                stack[top++] = value;
            else {
                int inside = 0;
                while (top > 0 && stack[top - 1] > 0)
                    inside += stack[--top];
                valid = top > 0 && stack[top - 1] + value == 0 &&
                        inside < value;
                if (valid)
                    stack[top - 1] = value;
            }
        }
        valid &= top == 0 || stack[top - 1] > 0;
        printf("%s\n", valid ? ":-) Matrioshka!" : ":-( Try again.");
    }
    return EXIT_SUCCESS;
}
