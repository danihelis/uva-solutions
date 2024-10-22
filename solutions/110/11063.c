/* 11063
 * B2-Sequence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   100
#define FIND(x,v,s,e) (bsearch(&x, (v) + (s), (e) - (s), sizeof (int), \
                            compare) != NULL)

/* Compare two integers */
int compare(const void *a, const void *b) {
    return * (int *) a - * (int *) b;
}

/* Main function */
int main() {
    int vector[MAX_N], n, test = 0;
    while (scanf("%d", &n) == 1) {
        int i, j, k, isB2;
        for (i = 0, isB2 = 1; i < n; i++) {
            assert(scanf("%d", &vector[i]) == 1);
            isB2 &= (i == 0 && vector[i] >= 1) || 
                (i > 0 && vector[i] > vector[i - 1]);
        }
        for (i = 0; isB2 && i < n; i++)
            for (j = i + 1; isB2 && j < n; j++) {
                int sum = vector[i] + vector[j];
                for (k = i + 1; isB2 && k < j && 
                        sum - vector[k] >= vector[k]; k++) {
                    int diff = sum - vector[k];
                    isB2 = !FIND(diff, vector, k, j);
                }
            }
        printf("Case #%d: It is%s a B2-Sequence.\n\n", ++test, 
                isB2 ? "" : " not");
    }

    return EXIT_SUCCESS;
}
