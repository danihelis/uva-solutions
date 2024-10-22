/* 11608
 * No Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define N   12

/* Main function */
int main() {
    int p, test = 0;
    while (scanf("%d", &p) == 1 && p >= 0) {
        int i, d[N], c[N];
        for (i = 0; i < N; i++)
            assert(scanf("%d", &c[i]) == 1);
        for (i = 0; i < N; i++)
            assert(scanf("%d", &d[i]) == 1);
        printf("Case %d:\n", ++test);
        for (i = 0; i < N; i++) {
            printf("No problem%s\n", p >= d[i] ? "! :D" : ". :(");
            if (p >= d[i])
                p = p - d[i];
            p += c[i];
        }
    }
    return EXIT_SUCCESS;
}
