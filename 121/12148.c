/* 12148
 * Electricity
 * by Iohan Schreiber
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MONTHS 12

typedef struct {
    int day, month, year;
} date_t;

int last[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* Check if year is leap year */
int leap_year(year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0); 
}

/* Compute next date after given date */
date_t next_date(date_t date) {
    date_t next = date;
    next.day++;
    if (next.month == 2 && next.day == 29 && leap_year(next.year)) {
        return next;
    }
    if (next.day > last[next.month - 1]) {
        next.day = 1, next.month++;
        if (next.month > 12) next.month = 1, next.year++;
    }
    return next;
}

/* Main function */
int main() {
    int n;
    while (scanf("%d", &n) != EOF && n > 0) {
        int days, amount, value, last_value;
        date_t last, date;
        for (last.day = days = amount = 0; n > 0; n--) {
            assert(scanf("%d %d %d %d", &date.day, &date.month, &date.year, 
                    &value) != EOF);
            if (last.day) {
                date_t next = next_date(last);
                if (next.day == date.day && next.month == date.month &&
                        next.year == date.year) {
                    days++, amount += value - last_value;
                }
            }
            last_value = value, last = date;
        }
        printf("%d %d\n", days, amount);
    }
    return EXIT_SUCCESS;
}
