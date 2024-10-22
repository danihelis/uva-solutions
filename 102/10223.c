/* 10223
 * How many nodes ?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_N   4294967295L
#define SIZE    50

long catalan[SIZE];
int size;

/* Compute catalan numbers up to MAX_N */
void compute_catalan() {
    int i;
    catalan[0] = 1;
    for (i = 1; catalan[i - 1] < MAX_N; i++) {
        long k = (4 * i - 2) * catalan[i - 1];
        catalan[i] = k / (i + 1);
    }
    size = i;
}

/* Main function */
int main() {
    long n;
    compute_catalan();
    while (scanf("%ld", &n) == 1) {
        int k;
        for (k = 1; catalan[k] < n; k++)
            ;
        printf("%d\n", k);
    }
    return EXIT_SUCCESS;
}
