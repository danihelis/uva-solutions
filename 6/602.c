/* 602
 * What Day Is It?
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  20

#define GREG_YEAR   1752
#define GREG_MONTH  9
#define GREG_DAY    2
#define GREG_NEXT   14
#define GREG_SKIP   2

#define NUM_MONTHS      12
#define NUM_DAYS_YEAR   365
#define NUM_DAYS_WEEK   7

typedef char string_t[MAX_STRING];

int days_month[NUM_MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string_t month_name[NUM_MONTHS] = {"January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"};
string_t weekday_name[NUM_DAYS_WEEK] = {"Friday", "Saturday", "Sunday", "Monday", "Tuesday",
    "Wednesday", "Thursday"};

/* Whether it is a leap year or not */
int is_leap_year(int y) {
    if (y <= GREG_YEAR) {
        return (y % 4) == 0 ? 1 : 0;
    }
    return (y % 400 == 0 ? 1 : y % 100 == 0 ? 0 : y % 4 == 0 ? 1 : 0);
}

/* Main function */
int main() {
    int month, day, year;
    while (scanf("%d %d %d", &month, &day, &year) != EOF && year > 0) {
        int i, total_days, leap = is_leap_year(year);
        if (month > NUM_MONTHS || day > days_month[month - 1] + (month == 2 ? leap : 0) ||
                (year == GREG_YEAR && month == GREG_MONTH && 
                 (day > GREG_DAY && day < GREG_NEXT))) {
            printf("%d/%d/%d is an invalid date.\n", month, day, year);
            continue;
        }
        total_days = NUM_DAYS_YEAR * (year - 1) + (year - 1) / 4;
        if (year > GREG_YEAR || (year == GREG_YEAR && 
                    (month > GREG_MONTH || (month == GREG_MONTH && day > GREG_DAY)))) {
            total_days -= (year - 1) / 100;
            total_days += (year - 1) / 400;
            total_days += GREG_SKIP; 
        }
        for (i = 0; i < month - 1; i++) {
            total_days += days_month[i] + (i == 1 ? leap : 0);
        }
        total_days += day;
        printf("%s %d, %d is a %s\n", month_name[month - 1], day, year, 
                weekday_name[total_days % 7]);
    }
    return 0;
}
