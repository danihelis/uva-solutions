/* 10114
 * Loansome Car Buyer
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_MONTHS 101

/* Main function */
int main() {
    int months, n;
    double down, loan;
    while (scanf("%d %lf %lf %d", &months, &down, &loan, &n) != EOF && months >= 0) {
        int i, m, month[MAX_MONTHS];
        double car, debt, porcent[MAX_MONTHS];
        for (i = 0; i < n; i++) {
            assert(scanf("%d %lf", &month[i], &porcent[i]) != EOF);
        }
        car = down + loan;
        for (i = 0, m = 0; m <= months; m++) {
            if (i < n && month[i] == m) {
                i++;
            }
            car -= car * porcent[i - 1];
            debt = loan - (m > 0 ? m * loan / months : 0);
            if (car > debt) {
                printf("%d month%s\n", m, m != 1 ? "s" : "");
                break;
            }
        }
    }
    return 0;
}
