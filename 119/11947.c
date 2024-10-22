/* 11947
 * Cancer or Scorpio
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_MONTHS  12
#define MAX_STRING  15
#define GESTATION   (40 * 7)

char zodiac[NUM_MONTHS][MAX_STRING] = {
    "aquarius",
    "pisces",
    "aries",
    "taurus",
    "gemini",
    "cancer",
    "leo",
    "virgo",
    "libra",
    "scorpio",
    "sagittarius",
    "capricorn"
};
int first_day[NUM_MONTHS] = {
    21,
    20,
    21,
    21,
    22,
    22,
    23,
    22,
    24,
    24,
    23,
    23
};
int days_month[NUM_MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* Get an extra day for a leap year */
int leap_day(int year) {
    return ((year % 4 == 0) && (year % 400 == 0 || year % 100 != 0)) ? 1 : 0;
}

/* Main function */
int main() {
    int test, num_tests;
    assert(scanf("%d ", &num_tests) != EOF);
    for (test = 1; test <= num_tests; test++) {
        char input[MAX_STRING];
        int leap, day, month, year;
        assert(scanf("%s ", input) != EOF);
        
        year = atoi(input + 4);
        input[4] = 0;
        day = atoi(input + 2);
        input[2] = 0;
        month = atoi(input) - 1;
        day += GESTATION;

        leap = leap_day(year);
        while (day > days_month[month] + (month == 1 ? leap : 0)) {
            day -= days_month[month] + (month == 1 ? leap : 0);
            month++;
            if (month >= NUM_MONTHS) {
                month = 0;
                year++;
                leap = leap_day(year); 
            }
        }

        printf("%d %02d/%02d/%04d ", test, month + 1, day, year);
        if (day < first_day[month]) {
            month = (NUM_MONTHS + month - 1) % NUM_MONTHS;
        }
        printf("%s\n", zodiac[month]);
    }
    return 0;
}
