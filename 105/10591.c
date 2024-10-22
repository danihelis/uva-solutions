/* 10591
 * Happy Number
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX     730

enum {
    UNKNOWN,
    VISITED,
    HAPPY,
    UNHAPPY
} state, table[MAX];

/* Compute the sum of square digits */
int sum(int n) {
    int s = 0;
    while (n > 0) {
        int d = (n % 10);
        s += d * d;
        n /= 10;
    }
    return s;
}

/* Compute table */
void compute_table() {
    int i, k, sequence[MAX];
    memset(table, UNKNOWN, MAX);
    table[1] = HAPPY;
    for (i = 2; i < MAX; i++) {
        for (k = 0, sequence[0] = i; table[sequence[k]] == UNKNOWN; k++) {
            table[sequence[k]] = VISITED;
            sequence[k + 1] = sum(sequence[k]);
        }
        state = table[sequence[k]] == VISITED ? UNHAPPY : table[sequence[k]];
        for (k--; k >= 0; k--) {
            table[sequence[k]] = state;
        }
    }
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    compute_table();
    for (test = 1; test <= num_tests; test++) {
        int n;
        assert(scanf("%d", &n) != EOF);
        state = n < MAX ? table[n] : table[sum(n)];
        printf("Case #%d: %d is a%sappy number.\n", test, n, state == HAPPY ? " H" : "n Unh");
    }
    return 0;
}
