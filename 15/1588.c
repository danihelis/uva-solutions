/* 1588
 * Kickdown
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100
#define MAX_LENGTH  (MAX_N + 2)

#define VALUE(x)    ((x) - '0')
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#define MAX(a, b)   ((a) > (b) ? (a) : (b))

/* Return smallest fit of a into b */
long fit(char *a, int a_len, char *b, int b_len) {
    char *i, *j, *k;
    for (i = a; *i; i++) {
        for (j = b, k = i; *j && *k && VALUE(*j) + VALUE(*k) <= 3; j++, k++)
            ;
        if (*j == 0 || *k == 0) break;
    }
    return MAX(a_len, (i - a) + b_len);
}

/* Main function */
int main() {
    char master[MAX_LENGTH], driven[MAX_LENGTH];
    int master_len, driven_len;
    long f1, f2;
    while (scanf(" %s", master) != EOF) {
        assert(scanf(" %s", driven) != EOF);
        master_len = strlen(master), driven_len = strlen(driven);
        f1 = fit(master, master_len, driven, driven_len);
        f2 = fit(driven, driven_len, master, master_len);
        printf("%ld\n", MIN(f1, f2));
    }
    return EXIT_SUCCESS;
}
