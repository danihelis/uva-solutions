/* 11172
 * Relational Operator
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int a, b, tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        assert(scanf("%d %d", &a, &b) != EOF);
        printf("%c\n", (a < b ? '<' : a > b ? '>' : '='));
    }
    return 0;
}
