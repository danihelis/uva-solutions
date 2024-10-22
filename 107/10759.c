/* 10759
 * Dice Throwing
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_DICE    24
#define MAX_SUM     150
#define MAX(x,y)    ((x) > (y) ? (x) : (y))

unsigned long prob[MAX_DICE + 1][MAX_SUM], den[MAX_DICE + 1];

/* Compute probablity of N dice rolling at least SUM: Nd6 >= SUM */
void compute() {
    int d, s, i, max;
    memset(prob[0], 0, MAX_SUM * sizeof (long));
    prob[0][0] = 1, den[0] = 1;
    for (d = 1; d <= MAX_DICE; d++) {
        den[d] = den[d - 1] * 6;
        for (s = 0; s <= d; s++)
            prob[d][s] = den[d];
        for (max = d * 6; s <= max; s++)
            for (i = 1, prob[d][s] = 0; i <= 6; i++)
                prob[d][s] += prob[d - 1][MAX(0, s - i)];
        for (; s < MAX_SUM; s++)
            prob[d][s] = 0;
    }
}

/* GCD */
unsigned long gcd(unsigned long a, unsigned long b) {
    while (b > 0) {
        unsigned long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/* Main function */
int main() {
    int d, s;
    compute();
    while (scanf("%d %d", &d, &s) == 2 && d > 0) {
        unsigned long nom = prob[d][s];
        if (nom == 0 || nom == den[d])
            printf("%lu\n", nom / den[d]);
        else {
            unsigned long g = gcd(nom, den[d]);
            printf("%lu/%lu\n", nom / g, den[d] / g);
        }
    }
    return EXIT_SUCCESS;
}
