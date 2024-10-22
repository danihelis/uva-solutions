/* 12342
 * Tax Calculator
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define LEVELS      5
#define MINIMUM     2000
#define CEIL(x, y)  (((x) + (y) - 1) / (y))
#define MIN(x, y)   ((x) < (y) ? (x) : (y))

long amount[LEVELS] = {180000, 300000, 400000, 300000, 1L << 31};
int tax[LEVELS] = {0, 10, 15, 20, 25};

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        long income, pay;
        int i;
        assert(scanf("%ld", &income) == 1);
        for (i = 0, pay = 0; i < LEVELS && income > 0; i++) {
            long parcel = MIN(income, amount[i]);
            pay += parcel * tax[i];
            income -= parcel;
        }
        pay = CEIL(pay, 100);
        if (pay > 0 && pay < MINIMUM)
            pay = MINIMUM;
        printf("Case %d: %ld\n", test, pay);
    }
    return EXIT_SUCCESS;
}
