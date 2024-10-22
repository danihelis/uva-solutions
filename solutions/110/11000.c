/* 11000
 * Bee
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_YEAR   50

/* Main function */
int main() {
    long fibbo[MAX_YEAR];
    int year, last_year = 2;
    fibbo[0] = 1, fibbo[1] = 1;
    while (scanf("%d", &year) != EOF && year >= 0) {
        for (; last_year <= year + 2; last_year++)
            fibbo[last_year] = fibbo[last_year - 1] + fibbo[last_year - 2];
        printf("%ld %ld\n", fibbo[year + 1] - 1, fibbo[year + 2] - 1);
    }
    return EXIT_SUCCESS;
}
