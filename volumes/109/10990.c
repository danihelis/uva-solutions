/* 10990
 * Another New Function
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M   2000000

int phi[MAX_M];
int df[MAX_M];
int sodf[MAX_M];

/* Compute sum of depth phi for all numbers */
void compute_sodf() {
    int i, k;

    for (i = 0; i < MAX_M; i++) {
        phi[i] = 1;
    }

    df[0] = 0;
    sodf[0] = 0;

    for (i = 1; i < MAX_M; i++) {
        if (phi[i] == 1) {
            long n, j;

            for (k = 0, n = i + 1; n <= MAX_M; k++, n *= i + 1) {
                if (i == 1 && k == 0) continue;
                for (j = n - 1; j < MAX_M; j += n) {
                    phi[j] *= i + (k == 0 ? 0 : 1);
                }
            }
        }
        assert(phi[i] <= i && phi[i] >= 1);
        df[i] = df[phi[i] - 1] + 1;
        sodf[i] = df[i] + sodf[i - 1];
    }
}

/* Main function */
int main() {
    int m, n, num_tests;

    compute_sodf();

    assert(scanf("%d", &num_tests) == 1);
    while (num_tests-- > 0) {
        assert(scanf("%d %d", &m, &n) == 2);
        printf("%d\n", sodf[n - 1] - sodf[m - 2]);
    }

    return EXIT_SUCCESS;
}
