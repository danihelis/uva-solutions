/* 10440
 * Ferry Loading II
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CARS        1500

int car[MAX_CARS];
int num_cars, time_cross, max_capacity;

/* Get minimum time and number of cars needed to cross all */
void get_minimum_time(int *last_time, int *num_crosses) {
    int stack[MAX_CARS];
    int top, i, time;
    for (top = 0, i = num_cars - 1; i >= 0; top++) {
        stack[top] = i;
        i -= max_capacity;
    }
    *num_crosses = top;
    for (time = 0, top--; top >= 0; top--) {
        int last = car[stack[top]];
        if (time < last) {
            time = last;
        }
        time += 2 * time_cross;
    }
    *last_time = time - time_cross;
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, time, crosses;
        assert(scanf("%d %d %d", &max_capacity, &time_cross, &num_cars) != EOF);
        for (i = 0; i < num_cars; i++) {
            assert(scanf("%d", &car[i]) != EOF);
        }
        get_minimum_time(&time, &crosses);
        printf("%d %d\n", time, crosses);

    }
    return 0;
}
