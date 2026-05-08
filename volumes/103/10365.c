/* 10365
 * Blocks
 * By Johan Schreiber
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N           1000
#define MAX_DIV         50

int divisors[MAX_N][MAX_DIV];
int num_divisors[MAX_N];

/* Compute all divisors for all numbers */
void compute_divisors() {
    int i, n;

    memset(num_divisors, 0, sizeof (int) * MAX_N);

    for (n = 1; n <= MAX_N; n++) {
        for (i = n; i <= MAX_N; i += n) {
            assert(num_divisors[i - 1] < MAX_DIV);
            divisors[i - 1][num_divisors[i - 1]++] = n;
        }
    }
}

/* Compute best area of N blocks */
int best_area(int n) {
    int m, a, b, c, ia, ib;
    int area, best = 0;

    for (ia = 0; ia < num_divisors[n - 1]; ia++) {
        a = divisors[n - 1][ia];
        m = n / a;
        if (m < a) break;

        for (ib = 0; ib < num_divisors[m - 1]; ib++) {
            b = divisors[m - 1][ib];
            if (b < a) continue;

            c = m / b;
            if (c < b) break;

            area = 2 * ((a * b) + (a * c) + (b * c));
            if (!best || area < best) best = area;
        }
    }
    return best;
}

/* Main function */
int main() {
    int num_tests, n;

    compute_divisors();
    assert(scanf("%d", &num_tests) == 1);

    while (num_tests-- > 0) {
        assert(scanf("%d", &n) == 1);
        printf("%d\n", best_area(n));
    }

    return EXIT_SUCCESS;
}
