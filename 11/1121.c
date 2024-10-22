/* 1121
 * Subsequence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N       100000
#define INFINITY    (MAX_N + 1)

/* Main function */
int main() {
    int vector[MAX_N];
    int n, s, i, start, sum, len;
    while (scanf("%d %d", &n, &s) != EOF) {
        for (i = start = sum = 0, len = INFINITY; i < n; i++) {
            assert(scanf("%d", &vector[i]) != EOF);
            sum += vector[i];
            if (sum >= s) {
                while (start < i && sum - vector[start] >= s)
                    sum -= vector[start++];
                if (i - start + 1 < len)
                    len = i - start + 1;
            }
        }
        printf("%d\n", len == INFINITY ? 0 : len);
    }
    return EXIT_SUCCESS;
}
