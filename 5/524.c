/* 524
 * Prime Ring Problem
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBER  17
#define MAX_SUM     32

int used[MAX_NUMBER], sequence[MAX_NUMBER];
int is_prime[MAX_SUM] = {
    0, 0, 1, 1, 0, 1, 0, 1, 0, 0,
    0, 1, 0, 1, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    0, 1};
int n;

/* Create sequence */
void create_sequence(int i) {
    int k;
    if (i >= n && is_prime[sequence[i - 1] + 1]) {
        for (k = 0; k < n; k++) {
            printf("%d%c", sequence[k], (k == n - 1 ? '\n' : ' '));
        }
    }
    else {
        for (k = 2; k <= n; k++) {
            if (!used[k] && is_prime[k + sequence[i - 1]]) {
                used[k] = 1;
                sequence[i] = k;
                create_sequence(i + 1);
                used[k] = 0;
            }
        }
    }
}

/* Main function */
int main() {
    int test = 0;
    sequence[0] = 1;
    while (scanf("%d", &n) != EOF) {
        memset(used, 0, (n + 1) * sizeof (int));
        printf("%sCase %d:\n", (test > 0 ? "\n" : ""), test + 1);
        create_sequence(1);
        test++;
    }
    return 0;
}
