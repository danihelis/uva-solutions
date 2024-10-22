/* 701
 * The Archeologists' Dilemma
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
    double lg2, lg10;
    int n;
    lg2 = log(2);
    lg10 = log(10) / lg2;
    while (scanf("%d", &n) != EOF) {
        int find = 0, k, p = log10(n) + 1;
        double lgn = log(n) / lg2, lgnp = log(n + 1) / lg2;
        while (!find) {
            double plg10 = ++p * lg10;
            k = ceil(lgn + plg10);
            find = k <= floor(lgnp + plg10);
        }
        printf("%d\n", k);
    }
    return 0;
}
