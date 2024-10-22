/* 11192
 * Group Reverse
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 150

/* Main function */
int main() {
    char input[MAX_STRING];
    int size;
    while (scanf("%d %s", &size, input) != EOF && size > 0) {
        char *i, *s, *e;
        size = strlen(input) / size;
        for (i = input; *i != 0; i += size)
            for (s = i, e = i + size - 1; s < e; s++, e--) {
                char swap = *s;
                *s = *e;
                *e = swap;
            }
        printf("%s\n", input);
    }
    return EXIT_SUCCESS;
}
