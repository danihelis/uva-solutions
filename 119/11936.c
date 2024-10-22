/* 11936
 * The Lazy Lumberjacks
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define SWAP(x,y) do  { \
        int _s = x; x = y; y = _s; \
    } while (0)

/* Main function */
int main() {
    int a, b, c;
    assert(scanf("%*d") != EOF);
    while (scanf("%d %d %d", &a, &b, &c) != EOF) {
        if (a < b)
            SWAP(a, b);
        if (a < c)
            SWAP(a, c);
        printf("%s\n", a < b + c ? "OK" : "Wrong!!");
    }
    return EXIT_SUCCESS;
}
