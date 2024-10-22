/* 10783
 * Odd Sum
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TABLE       101
#define MAX(x, y)       ((x) > (y) ? (x) : (y))

/* Main function */
int main() {
    int i, table[MAX_TABLE], test, num_tests;
    for (i = 1, table[0] = 0; i < MAX_TABLE; i++) {
        table[i] = table[i - 1] + (i % 2 == 1 ? i : 0);
    }
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int floor, ceil;
        assert(scanf("%d %d", &floor, &ceil) != EOF);
        printf("Case %d: %d\n", test, table[ceil] - table[MAX(floor - 1, 0)]);
    }
    return 0;
}
