/* 12019
 * Doom's Day Algorithm
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MONTHS  12
#define DAYS    365
#define WEEK    7
#define STRING  10

int days[MONTHS] = {31, 28, 31, 30, 31, 30, 31,
    31, 30, 31, 30, 31};
int weekday[DAYS];
char name[WEEK][STRING] = {"Sunday", "Monday", "Tuesday",
    "Wednesday", "Thursday", "Friday", "Saturday"};

/* Main function */
int main() {
    int i, j, d, num_tests;
    for (i = 0, d = 1, weekday[0] = 6; i < MONTHS; i++) {
        for (j = i == 0 ? 1 : 0; j < days[i]; j++, d++)
            weekday[d] = (weekday[d - 1] + 1) % WEEK;
        days[i] = d - days[i];
    }
    assert(scanf("%d", &num_tests) == 1);
    for (; num_tests > 0; num_tests--) {
        assert(scanf("%d %d", &i, &j) == 2);
        d = days[i - 1] + j;
        printf("%s\n", name[weekday[d - 1]]);
    }
    return EXIT_SUCCESS;
}
