/* 11530
 * SMS Typing
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_INPUT   200

char button[4][20] = {
    "adgjmptw ",
    "behknqux",
    "cfilorvy",
    "sz"
};

/* Main function */
int main() {
    int test = 0;
    char *p, line[MAX_INPUT];
    while (fgets(line, MAX_INPUT, stdin) != NULL) {
        if (test > 0) {
            int i, sum;
            for (p = line, sum = 0; *p != '\n'; p++)
                for (i = 0; i < 4; i++)
                    if (strchr(button[i], *p) != NULL)
                        sum += i + 1;
            printf("Case #%d: %d\n", test, sum);
        }
        test++;
    }
    return EXIT_SUCCESS;
}
