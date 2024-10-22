/* 12289
 * One-Two-Three
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  10
#define IS(i, c)    (string[i] == (c) ? 1 : 0)

/* Main function */
int main() {
    char string[MAX_STRING];
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf(" %s", string) != EOF);
        if (string[3] != 0) {
            printf("3\n");
        }
        else {
            int one, two;
            one = IS(0, 'o') + IS(1, 'n') + IS(2, 'e');
            two = IS(0, 't') + IS(1, 'w') + IS(2, 'o');
            printf("%s\n", one > two ? "1" : "2");
        }
    }
    return 0;
}
