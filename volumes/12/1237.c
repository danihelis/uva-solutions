/* 1237
 * Expert Enough?
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CARS    10000
#define MAX_NAME    25
#define NONE        -1
#define MULTIPLES   -2

typedef struct {
    char name[MAX_NAME];
    int min, max;
} car_t;

car_t car[MAX_CARS], *p_car[MAX_CARS];
int num_cars;

/* Compare cars by max value */
int compare(const void *a, const void *b) {
    return (* (car_t **) b)->max - (* (car_t **) a)->max;
}

/* Main function */
int main() {
    int tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        int i, queries;
        assert(scanf("%d", &num_cars) != EOF);
        for (i = 0; i < num_cars; i++) {
            assert(scanf(" %s %d %d", car[i].name, &car[i].min, &car[i].max)
                    != EOF);
            p_car[i] = &car[i];
        }
        qsort(p_car, num_cars, sizeof (car_t *), compare);
        assert(scanf("%d", &queries) != EOF);
        for (; queries > 0; queries--) {
            int value, which;
            assert(scanf("%d", &value) != EOF);
            for (i = 0, which = NONE; which != MULTIPLES && i < num_cars && 
                    value <= p_car[i]->max; i++) {
                if (value >= p_car[i]->min)
                    which = which == NONE ? i : MULTIPLES;
            }
            printf("%s\n", which >= 0 ? p_car[which]->name : "UNDETERMINED");
        }
        if (tests > 1) 
            printf("\n");
    }
    return 0;
}
