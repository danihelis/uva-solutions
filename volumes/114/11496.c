/* 11496
 * Musical Loop
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N   10002

/* Main function */
int main() {
    int vector[MAX_N];
    int i, n, peaks;
    while (scanf("%d", &n) == 1 && n) {
        for (i = 1; i <= n; i++) {
            assert(scanf("%d", &vector[i]) == 1);
        }
        vector[0] = vector[n];
        vector[n + 1] = vector[1];

        for (i = 1, peaks = 0; i <= n; i++) {
            if ((vector[i] > vector[i - 1] && vector[i] > vector[i + 1]) ||
                    (vector[i] < vector[i - 1] && vector[i] < vector[i + 1])) {
                peaks++;
            }
        }
        printf("%d\n", peaks);
    }
    return EXIT_SUCCESS;
}
