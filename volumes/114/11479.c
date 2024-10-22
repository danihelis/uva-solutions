/* 11479
 * Is this the easiest problem?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX(x, y)   ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    int a, b, c, max, test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 0; test < num_tests; test++) {
        assert(scanf("%d %d %d", &a, &b, &c) != EOF);
        max = MAX(a, b);
        max = MAX(max, c);
        printf("Case %d: ", test + 1);
        if (2 * max >= a + b + c) {
            printf("Invalid\n");
        }
        else if (a == b && b == c) {
            printf("Equilateral\n");
        }
        else if (a == b || b == c || a == c) {
            printf("Isosceles\n");
        }
        else {
            printf("Scalene\n");
        }
    }
    return 0;
}
