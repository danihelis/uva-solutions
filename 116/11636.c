/* 11636
 * Hello World!
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
    int test = 0, n, pastes, total;
    while (scanf("%d", &n) != EOF && n > 0) {
        for (pastes = 0, total = 1; total < n; pastes++, total <<= 1)
            ;
        printf("Case %d: %d\n", ++test, pastes);
    }
    return 0;
}
