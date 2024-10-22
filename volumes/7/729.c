/* 729
 * The Hamming Distance Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_BITS    17

char bit[MAX_BITS];
int n;

/* Print all bit sequences with the given hamming distance from 0 */
void print_sequence(int pos, int ones) {
    assert(n - pos >= ones);
    if (n - pos == ones || ones == 0) {
        for (; pos < n; pos++) {
            bit[pos] = (ones == 0 ? '0' : '1');
        }
        bit[pos] = 0;
        printf("%s\n", bit);
    }
    else {
        bit[pos] = '0';
        print_sequence(pos + 1, ones);
        bit[pos] = '1';
        print_sequence(pos + 1, ones - 1);
    }
}

/* Main function */
int main() {
    int num_tests, hamming;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d %d", &n, &hamming) != EOF);
        print_sequence(0, hamming);
        (num_tests > 1 ? printf("\n") : 0);
    }
    return 0;
}
