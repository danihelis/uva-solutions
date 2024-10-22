/* 297
 * Quadtrees
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_LEVEL   32
#define MAX_STRING  2000
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

/* Consume a quadrant and return the number of black pixels */
int consume(char **q, int level) {
    char type = **q;
    int total, i;
    (*q)++;
    switch (type) {
        case 'f': return level * level;
        case 'e': return 0;
        case 'p':
            for (i = 0, total = 0; i < 4; i++) {
                total += consume(q, level / 2);
            }
            return total;
    }
    assert(NULL);
    return 0;
}

/* Combine two pictures recursively and return the number of black pixels */
int combine(char **a, char **b, int level) {
    int i, total = 0;
    if (**a == 'p' && **b == 'p') {
        (*a)++, (*b)++;
        for (i = 0; i < 4; i++) {
            total += combine(a, b, level / 2);
        }
    }
    else {
        int ta = consume(a, level), tb = consume(b, level);
        total = MAX(ta, tb);
    }
    return total;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        char a[MAX_STRING], b[MAX_STRING], *pa, *pb;
        pa = a, pb = b;
        assert(scanf(" %s %s", a, b) != EOF);
        printf("There are %d black pixels.\n", combine(&pa, &pb, MAX_LEVEL));
    }
    return 0;
}
