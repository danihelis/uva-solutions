/* 412
 * Pi
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS     50

int number[MAX_NUMBERS];

/* Greatest common divisor between two numbers */
int gcd(int a, int b) {
    while (a != b) {
        if (a > b) {
            a -= b;
        }
        else {
            b -= a;
        }
    }
    return a;
}

/* Main function */
int main() {
    int num_numbers;
    while (scanf("%d", &num_numbers) != EOF && num_numbers > 0) {
        int i, j, total, non_common;
        for (i = 0, non_common = 0, total = 0; i < num_numbers; i++) {
            assert(scanf("%d", &number[i]) != EOF);
            for (j = 0; j < i; j++, total++) {
                non_common += (gcd(number[j], number[i]) == 1 ? 1 : 0);
            }
        }
        if (non_common == 0) {
            printf("No estimate for this data set.\n");
        }
        else {
            printf("%.6f\n", sqrt(6.0 * total / non_common));
        }
    }
    return 0;
}
