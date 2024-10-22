/* 300
 * Maya Calendar
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_DAYS            20
#define NUM_HAAB_MONTHS     19
#define NUM_TZOLKIN_PERIODS 13
#define MAX_STRING          15

#define LEN_HAAB_YEAR       365
#define LEN_TZOLKIN_YEAR    (NUM_TZOLKIN_PERIODS * NUM_DAYS)

char haad_month[NUM_HAAB_MONTHS][MAX_STRING] = {
    "pop", "no", "zip", "zotz", "tzec", "xul", 
    "yoxkin", "mol", "chen", "yax", "zac", "ceh", 
    "mac", "kankin", "muan", "pax", "koyab", "cumhu",
    "uayet"
};
char tzolkin_day[NUM_DAYS][MAX_STRING] = {
    "imix", "ik", "akbal", "kan", "chicchan",
    "cimi", "manik", "lamat", "muluk", "ok", 
    "chuen", "eb", "ben", "ix", "mem", 
    "cib", "caban", "eznab", "canac", "ahau"
};

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) == 1);
    printf("%d\n", num_tests);
    for (; num_tests > 0; num_tests--) {
        int h_day, h_month, h_year, total, t_day, t_period, t_year;
        char name[MAX_STRING];
        assert(scanf("%d. %s %d", &h_day, name, &h_year) == 3);
        for (h_month = 0; h_month < NUM_HAAB_MONTHS && 
                strcmp(name, haad_month[h_month]) != 0; h_month++)
            ;
        assert(h_month < NUM_HAAB_MONTHS);
        total = h_year * LEN_HAAB_YEAR + h_month * NUM_DAYS + h_day;
        t_year = total / LEN_TZOLKIN_YEAR;
        total %= LEN_TZOLKIN_YEAR;
        t_day = total % NUM_DAYS, t_period = 1 + (total % NUM_TZOLKIN_PERIODS);
        printf("%d %s %d\n", t_period, tzolkin_day[t_day], t_year);
    }
    return EXIT_SUCCESS;
}
