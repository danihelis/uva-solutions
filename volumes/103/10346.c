/* 10346
 * Peter's Smokes
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
    int n, k, b, t;
    while (scanf("%d %d", &n, &k) != EOF) {
        t = n, b = n;
        while (b >= k) {
            n = b / k;
            t += n, b += n - n * k;
        }
        printf("%d\n", t);
    }
    return 0;
}
