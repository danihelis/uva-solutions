/* 10137
 * The Trip
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
    int n; 
    while (scanf("%d", &n) != EOF && n > 0) {
        int i, dollar, cents, average, spent[MAX_STUDENTS];
        int debt, refund; 
        for (i = 0, average = 0; i < n; i++) {
            assert(scanf("%d.%d", &dollar, &cents) != EOF);
            spent[i] = dollar * 100 + cents;
            average += spent[i];
        }
        for (i = 0, average /= n, debt = 0, refund = 0; i < n; i++) {
            if (spent[i] < average) {
                debt += average - spent[i];
            }
            else if (spent[i] > average + 1) {
                refund += spent[i] - average - 1;
            }
        }
        dollar = debt < refund ? refund : debt;
        printf("$%d.%02d\n", dollar / 100, dollar % 100);
    }
    return 0;
}
