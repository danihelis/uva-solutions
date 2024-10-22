/* 893
 * Y3K Problem
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

int days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int num_months = sizeof (days_month) / sizeof (int);
const int days_year = 365;

/* One extra day for leap years */
int leap_extra_day(int year) {
    return (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0)) ? 1 : 0;
}


/* Count the number of leap years in this era */
int count_leaps(int year) {
    return (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
}


/* Increase data by n days */
void increase(int *day, int *month, int *year, int n) {
    int i, leap = leap_extra_day(*year);
    n += *day - 1;
    for (i = 0; i < *month - 1; i++) {
        n += days_month[i] + (i == 1 ? leap : 0);
    }
    *day = 1;
    *month = 1;
    while (n > 0) {
        if (n < days_year + leap) {
            *day = n + 1;
            days_month[1] += leap;
            for (i = 0; *day > days_month[i]; i++) {
                *day -= days_month[i];
            }
            days_month[1] -= leap;
            *month = i + 1;
            n = 0;
        }
        else if (n == days_year + leap) {
            (*year)++;
            n = 0;
        }
        else {
            int new_year = *year + n / (days_year + 1);
            n %= (days_year + 1);
            n += (new_year - count_leaps(new_year)) - (*year - count_leaps(*year));
            *year = new_year;
            leap = leap_extra_day(*year);
        }
    }
}

/* Main function */
int main() {
    int n, day, month, year;
    while (scanf("%d %d %d %d", &n, &day, &month, &year) != EOF && day > 0) {
        increase(&day, &month, &year, n);
        printf("%d %d %d\n", day, month, year);
    }
    return 0;
}
