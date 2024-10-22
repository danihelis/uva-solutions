/* 11849
 * CD
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CDS   1000000

/* Main function */
int main() {
    int cd[MAX_CDS], n, m, i, j, common, which;
    while (scanf("%d %d", &n, &m) != EOF && n > 0 && m > 0) {
        for (i = 0; i < n; i++) {
            assert(scanf("%d", &cd[i]) != EOF);
        }
        for (i = 0, j = 0, common = 0; j < m; j++) {
            assert(scanf("%d", &which) != EOF);
            for (; i < n && cd[i] < which; i++)
                ;
            common += (i < n && cd[i] == which) ? 1 : 0;
        }
        printf("%d\n", common);
    }
    return 0;
}
