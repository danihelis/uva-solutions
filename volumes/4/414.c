/* 414
 * Machined Surfaces
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  30

/* Main function */
#define READ(x)     (fgets(x, MAX_STRING, stdin) != NULL)
int main() {
    char line[MAX_STRING], *p;
    int n, i, spaces, minimum, count;
    while (READ(line) && (n = atoi(line)) > 0) {
        for (i = 0, spaces = 0, minimum = MAX_STRING; i < n; i++) {
            assert(READ(line));
            for (p = line, count = 0; *p != '\n'; p++) {
                count += *p == ' ' ? 1 : 0;
            }
            spaces += count;
            minimum = count < minimum ? count : minimum;
        }
        spaces -= n * minimum;
        printf("%d\n", spaces);
    }
    return 0;
}
