/* 10340
 * All in All
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING      1000000

/* Main function */
int main() {
    char string[MAX_STRING];
    while (scanf(" %s", string) != EOF) {
        char *p, c;
        for (p = string, c = 0; c != '\n'; assert(scanf("%c", &c) != EOF)) {
            if (*p == c) {
                p++;
            }
        }
        printf("%s\n", (*p == 0 ? "Yes" : "No"));
    }
    return 0;
}
