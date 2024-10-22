/* 10905
 * Children's Game
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       50
#define MAX_STRING  110

char vector[MAX_N][MAX_STRING], *sorted[MAX_N];

/* Compare two strings */
int compare(const void *a, const void *b) {
    char *x = * (char **) b, *y = * (char **) a;
    int lenx = strlen(x), leny = strlen(y);
    int len = lenx < leny ? lenx : leny;
    if (strncmp(x, y, len) == 0) {
        if (lenx != leny) {
            x += lenx < leny ? 0 : len, y += leny < lenx ? 0 : len;
            return compare(&y, &x);
        }
        else
            return 0;
    }
    return strcmp(x, y);
}

/* Main function */
int main() {
    int i, n;
    while (scanf("%d", &n) == 1 && n > 0) {
        for (i = 0; i < n; i++) {
            assert(scanf(" %s", vector[i]) == 1);
            sorted[i] = vector[i];
        }
        qsort(sorted, n, sizeof (char *), compare);
        for (i = 0; i < n; i++)
            printf("%s", sorted[i]);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
