/* 13275
 * Leap Birthdays
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
    int test, num_tests;
    assert(scanf("%d", &num_tests) == 1);
    for (test = 1; test <= num_tests; test++) {
        int day, month, year, query, total;
        assert(scanf("%d %d %d %d", &day, &month, &year, &query) == 4);
        if (day != 29 || month != 2)
            total = query - year;
        else
            for (++year, total = 0; year <= query; year++)
                total += year % 4 == 0 && 
                        (year % 400 == 0 || year % 100 != 0) ? 1 : 0;
        printf("Case %d: %d\n", test, total);
    }
    return EXIT_SUCCESS;
}
