/* 10970
 * Big Chocolate
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
    int m, n;
    while (scanf("%d %d", &m, &n) != EOF) {
        printf("%d\n", m * n - 1);
    }
    return 0;
}
