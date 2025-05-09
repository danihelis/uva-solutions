/* 580
 * Critical Mass
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N   30

int critical[MAX_N + 1];


/* Compute critical mass. C(n) = 0 if n < 3, else:
 * C(n) = 2^(n-3) + C(n-1) + C(n-2) + C(n-3)
 */
void compute_critical() {
    int i, j;
    for (i = 0; i <= MAX_N; i++) {
        if (i < 3) critical[i] = 0;
        else {
            critical[i] = 1 << (i - 3);
            for (j = 1; j <= 3; j++) {
                critical[i] += critical[i - j];
            }
        }
    }
}

/* Main function */
int main() {
    int n;
    compute_critical();
    while (scanf("%d", &n) == 1 && n > 0) {
        assert(n <= MAX_N);
        printf("%d\n", critical[n]);
    }
    return EXIT_SUCCESS;
}
