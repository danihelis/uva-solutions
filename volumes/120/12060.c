/* 12060
 * All Integer Average
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  10

/* Greates common divisor */
int gcd(int a, int b) {
    int m = a % b;
    while (m > 0) {
        a = b;
        b = m;
        m = a % b;
    }
    return b;
}

/* Number of digits */
int num_digits(int n) {
    int total = 1;
    while (n >= 10) {
        total++;
        n /= 10;
    }
    return total;
}

/* Main function */
int main() {
    int test = 0, n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int i, sum, avg, nom, factor, is_neg;
        char format[MAX_STRING];
        printf("Case %d:", ++test);
        for (i = 0, sum = 0; i < n; i++) {
            assert(scanf("%d", &factor) != EOF);
            sum += factor;
        }
        is_neg = sum < 0;
        sum = is_neg ? 0 - sum : sum;
        avg = sum / n;
        nom = sum % n;
        factor = gcd(nom, n);
        nom /= factor;
        n /= factor;
        if (n == 1) {
            printf("\n%s%d\n", is_neg ? "- " : "", avg);
        }
        else {
            factor = num_digits(n);
            sprintf(format, "\n%%%dd\n", factor + (avg > 0 ? num_digits(avg) : 0) 
                    + (is_neg ? 2 : 0));
            printf(format, nom);
            (avg > 0 ? printf("%s%d", is_neg ? "- " : "", avg) : is_neg ? printf("- ") : 0);
            for (i = 0; i < factor; i++) {
                printf("-");
            }
            printf(format, n);
        }
    }
    return 0;
}
