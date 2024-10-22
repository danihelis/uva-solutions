/* 1709
 * Amalgamated Artichokes
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

int p, a, b, c, d, n;

/* Compute stock price from given equation */
double eval(int k) {
    return (double) p * (sin(a * k + b) + cos(c * k + d) + 2.0);
}

/* Main function */
int main() {
    while (scanf("%d %d %d %d %d %d", &p, &a, &b, &c, &d, &n) != EOF) {
        double highest, max_decrease;
        int k;
        max_decrease = 0;
        highest = eval(1);
        for (k = 2; k <= n; k++) {
            double value = eval(k);
            if (value > highest) highest = value;
            else if (highest - value > max_decrease) {
                max_decrease = highest - value;
            }
        }
        printf("%.7f\n", max_decrease);
    }
    return EXIT_SUCCESS;
}
