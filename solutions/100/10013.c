/* 10013
 * Super long sums
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE    1000000

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int a[MAX_SIZE], b[MAX_SIZE];
        int i, carry, size;
        assert(scanf("%d", &size) != EOF);
        for (i = 0; i < size; i++)
            assert(scanf("%d %d", &a[i], &b[i]) != EOF);
        for (i = size - 1, carry = 0; i >= 0; i--) {
            carry += a[i] + b[i];
            a[i] = carry % 10;
            carry /= 10;
        }
        if (carry > 0)
            printf("%d", carry);
        for (i = 0; i < size; i++)
            printf("%0d", a[i]);
        printf("\n%s", num_tests > 1 ? "\n" : "");
    }
    return EXIT_SUCCESS;
}
