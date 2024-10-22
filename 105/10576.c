/* 10576
 * Y2K Accounting Bug
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MONTHS      12
#define LAST        5

int surplus, defict, best;
int sum[MONTHS + 1];

/* Compute recursivelly possibly best surplus */
void compute(int month) {
    int k;
    if (month > MONTHS) {
        if (sum[MONTHS] > best)
            best = sum[MONTHS];
        return;
    }
    for (k = 0; k < 2; k++) {
        sum[month] = sum[month - 1] + (k ? surplus : 0 - defict);
        if (month >= LAST && sum[month] - sum[month - LAST] >= 0)
            continue;
        if (sum[month] + (MONTHS - month) * surplus <= best)
            continue;
        compute(month + 1);
    }
}

/* Main function */
int main() {
    sum[0] = 0;
    while (scanf("%d %d", &surplus, &defict) != EOF) {
        best = -1;
        compute(1);
        (best < 0 ? printf("Deficit\n") : printf("%d\n", best));
    }
    return EXIT_SUCCESS;
}
