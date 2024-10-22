/* 10012
 * How Big Is It?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   8

double radius[MAX_N], sequence[MAX_N], position[MAX_N], best;
char used[MAX_N];
int n;

/* Compute best permutation */
void compute_best(int index) {
    double length;
    int i, j;
    if (index == n) {
        length = 0;
        for (i = 0; i < n; i++) {
            double p = position[i] + sequence[i];
            if (p > length)
                length = p;
        }
        if (length < best)
            best = length;
    }
    else {
        for (i = 0; i < n; i++)
            if (!used[i]) {
                used[i] = 1;
                sequence[index] = radius[i];
                length = radius[i];
                if (index > 0) {
                    for (j = 0; j < index; j++) {
                        double p = position[j] + 
                                2 * sqrt(radius[i] * sequence[j]);
                        if (p > length)
                            length = p;
                    }
                }
                position[index] = length;
                if (length + radius[i] < best)
                    compute_best(index + 1);
                used[i] = 0;
            }
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i;
        assert(scanf("%d", &n) != EOF);
        for (i = 0, best = HUGE_VAL; i < n; i++) {
            assert(scanf("%lf", &radius[i]) != EOF);
            used[i] = 0;
        }
        compute_best(0);
        printf("%.3f\n", best);
    }
    return EXIT_SUCCESS;
}
