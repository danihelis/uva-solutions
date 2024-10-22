/* 11219
 * How old are you?
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
    assert(scanf("%d", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        int cday, cmonth, cyear, bday, bmonth, byear, age;
        assert(scanf("%d/%d/%d %d/%d/%d", &cday, &cmonth, &cyear, &bday, 
                &bmonth, &byear) != EOF);
        age = cyear - byear;
        if (cmonth < bmonth || (bmonth == cmonth && cday < bday))
            age--;
        printf("Case #%d: ", test);
        if (age < 0 || age > 130)
            printf("%s birth date\n", age < 0 ? "Invalid" : "Check");
        else
            printf("%d\n", age);
    }
    return EXIT_SUCCESS;
}
