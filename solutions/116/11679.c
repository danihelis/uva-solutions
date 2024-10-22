/* 11679
 * Sub-prime
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   20

/* Main function */
int main() {
    int num_banks, num_debts;
    while (scanf("%d %d", &num_banks, &num_debts) == 2 && num_banks > 0) {
        int i, j, value, possible, reserve[MAX_N];
        for (i = 0; i < num_banks; i++)
            assert(scanf("%d", &reserve[i]) == 1);
        for (; num_debts > 0; num_debts--) {
            assert(scanf("%d %d %d", &i, &j, &value) == 3);
            --i, --j;
            reserve[i] -= value, reserve[j] += value;
        }
        for (i = 0, possible = 1; possible && i < num_banks; i++)
            possible = reserve[i] >= 0;
        printf("%s\n", possible ? "S" : "N");
    }
    return EXIT_SUCCESS;
}
