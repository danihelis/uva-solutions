/* 10370
 * Above Average
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STUDENTS    1000

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, n, above, sum, student[MAX_STUDENTS];
        assert(scanf("%d", &n) != EOF);
        for (i = 0, sum = 0; i < n; i++) {
            assert(scanf("%d", &student[i]) != EOF);
            sum += student[i];
        }
        for (i = 0, above = 0; i < n; i++) {
            above += ((student[i] * n) > sum ? 1 : 0);
        }
        printf("%.3f%%\n", above * 100.0 / (double) n);
    }
    return 0;
}
