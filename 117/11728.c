/* 11728
 * Alternate Task
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TABLE   1000

/* Get the sum of its factors */
int factor_sum(int n) {
    int i, sum;
    for (i = 2, sum = 1; i * 2 <= n; i++)
        sum += n % i == 0 ? i : 0;
    return sum + n;
}

/* Main function */
int main() {
    int test, n, table[MAX_TABLE];
    memset(table, -1, sizeof (table));
    table[0] = 1;
    for (n = 2; n < MAX_TABLE; n++) {
        int sum = factor_sum(n);
        if (sum <= MAX_TABLE)
            table[sum - 1] = n;
    }
    test = 0;
    while (scanf("%d", &n) != EOF && n > 0)
        printf("Case %d: %d\n", ++test, table[n - 1]);
    return EXIT_SUCCESS;
}
