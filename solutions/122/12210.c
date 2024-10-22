/* 12210
 * A Match Making Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    int i, extra, size, valor, minimum, test = 0;
    while (scanf("%d %d", &size, &extra) != EOF && size > 0) {
        for (i = 0; i < size; i++) {
            assert(scanf("%d", &valor) != EOF);
            if (i == 0 || valor < minimum)
                minimum = valor;
        }
        for (i = 0; i < extra; i++)
            assert(scanf("%*d") != EOF);
        printf("Case %d: ", ++test);
        if (size > extra)
            printf("%d %d\n", size - extra, minimum);
        else
            printf("0\n");
    }
    return EXIT_SUCCESS;
}
