/* 10190
 * Divide, But Not Quite Conquer!
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_K   32

/* Main function */
int main() {
    int n, m, seq[MAX_K];
    while (scanf("%d %d", &n, &m) == 2) {
        int i, k, valid;
        for (k = 0, valid = n > 1 && m > 1; valid && n > 1; n /= m, k++) {
            seq[k] = n;
            valid = n % m == 0;
        }
        if (!valid)
            puts("Boring!");
        else {
            for (i = 0; i < k; i++)
                printf("%s%d", i == 0 ? "" : " ", seq[i]);
            printf("%s1\n", k == 0 ? "" : " ");
        }
    }
    return EXIT_SUCCESS;
}
