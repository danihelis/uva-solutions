/* 12372
 * Packing for Holiday
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SIZE 20

/* Main function */
int main() {
    int a, b, c, test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        assert(scanf("%d %d %d", &a, &b, &c) != EOF);
        printf("Case %d: %s\n", test, (a <= SIZE && b <= SIZE && c <= SIZE) ? "good" : "bad");
    }
    return 0;
}
