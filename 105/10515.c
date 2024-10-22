/* 10515
 * Powers Et Al.
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  120
#define MAX_DIGITS  12

typedef struct {
    char digits[MAX_DIGITS];
    int total, cycle, offset;
} cycle_t;

cycle_t cycle[10] = {
    {"10", 2, 1, 1},
    {"1", 1, 1, 0},
    {"12486", 5, 4, 1},
    {"1397", 4, 4, 0},
    {"146", 3, 2, 1},
    {"15", 2, 1, 1},
    {"16", 2, 1, 1},
    {"1793", 4, 4, 0},
    {"18426", 5, 4, 1},
    {"19", 2, 2, 0}
};

/* Compute modulo */
int modulo(char *n, int div) {
    int m;
    for (m = 0; *n != 0; n++)
        m = (m * 10 + *n - '0') % div;
    return m;
}

/* Main function */
int main() {
    char a[MAX_STRING], b[MAX_STRING];
    while (scanf(" %s %s", a, b) == 2 && 
            (strcmp(a, "0") != 0 || strcmp(b, "0") != 0)) {
        cycle_t *c = &cycle[a[strlen(a) - 1] - '0'];
        int m, i;
        if (strlen(b) == 1 && (m = b[0] - '0') < c->total)
            i = m;
        else {
            m = (modulo(b, c->cycle) + c->cycle - c->offset) % c->cycle;
            i = m + c->offset;
        }
        printf("%c\n", c->digits[i]);
    }
    return EXIT_SUCCESS;
}
