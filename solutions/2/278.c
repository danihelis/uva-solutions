/* 278
 * Chess
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define CEIL_HALF(x)    (((x) + 1) / 2)
#define FLOOR_HALF(x)   ((x) / 2)
#define MIN(x,y)        ((x) < (y) ? (x) : (y))

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests));
    for (; num_tests > 0; num_tests--) {
        char type;
        int m, n, r;
        assert(scanf(" %c %d %d", &type, &m, &n) != EOF);
        switch (type) {
            case 'r':
            case 'Q': r = MIN(m, n); break;
            case 'k': r = FLOOR_HALF(n) * (CEIL_HALF(m) + FLOOR_HALF(m)) + 
                              (n % 2 == 0 ? 0 : CEIL_HALF(m)); break;
            case 'K': r = CEIL_HALF(m) * CEIL_HALF(n); break;
        }
        printf("%d\n", r);
    }
    return 0;
}
