/* 10055
 * Hashmat the Brave Warrior
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define ABS(x, y) (x > y ? x - y : y - x)

/* Main function */
int main() {
    long his, others;
    while (scanf("%ld %ld", &his, &others) != EOF) {
        printf("%ld\n", ABS(others, his));
    }
    return 0;
}
