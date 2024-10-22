/* 694
 * The Collatz Sequence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

/* Main function */
int main() {
    long start, value, cycle, limit, test = 1;
    while (scanf("%ld %ld", &start, &limit) != EOF && (start > 0 && limit > 0)) {
        value = start, cycle = 1;
        while (value > 1) {
            value = (value % 2 == 0 ? value / 2 : value * 3 + 1);
            if (value > limit) {
                break;
            }
            cycle++;
        }
        printf("Case %ld: A = %ld, limit = %ld, number of terms = %ld\n", 
                test++, start, limit, cycle);
    }
    return 0;
}
