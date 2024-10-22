/* 10071
 * Back to High School Physics
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
    int v, t;
    while (scanf("%d %d", &v, &t) != EOF) {
        printf("%d\n", 2 * v * t);
    }
    return 0;
}
