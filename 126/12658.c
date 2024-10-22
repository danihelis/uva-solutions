/* 12658
 * Character Recognition?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       10
#define MAX_STRING  (MAX_N * 5)
#define NUM_LINES   5
#define LINE        3

/* Main function */
int main() {
    int i, n;
    char line[MAX_STRING], *c;
    assert(scanf("%d %*s %*s %*s %s %*s", &n, line) == 2);
    for (i = 0, c = line; i < n; i++, c += 4) {
        printf("%d", *c == '*' ? 2 : *(c + 1) == '*' ? 1 : 3);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
