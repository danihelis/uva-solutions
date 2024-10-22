/* 10364
 * Square
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_OBJECTS 20

int object[MAX_OBJECTS];
char used[MAX_OBJECTS];
int num_objects, length_goal;

/* Recursivelly try to create a square side that matches the length goal */
int can_create_subset(int length, int steps, int index) {
    if (length > length_goal) {
        return 0;
    }
    else if (steps == 4 || length == length_goal) {
        int start;
        steps--;
        if (steps == 0) {
            return 1;
        }
        for (start = 0; start < num_objects && used[start]; start++)
            ;
        assert(start < num_objects);
        used[start] = 1;
        if (can_create_subset(object[start], steps, start + 1)) {
            return 1;
        }
        used[start] = 0;
        return 0;
    }
    else {
        int previous_length = -1;
        for (; index < num_objects; index++) {
            if (used[index] || object[index] == previous_length || 
                    length + object[index] > length_goal) {
                continue;
            }
            used[index] = 1;
            previous_length = object[index];
            if (can_create_subset(length + previous_length, steps, index + 1)) {
                return 1;
            }
            used[index] = 0;
        }
        return 0;
    }
}

/* Compare two integers in order to sort them */
int compare_int(const void *a, const void *b) {
    return *((int *) b) - *((int *) a);
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i, sum;
        assert(scanf("%d", &num_objects) != EOF);
        for (i = 0, sum = 0; i < num_objects; i++) {
            assert(scanf("%d", &object[i]) != EOF);
            sum += object[i];
        }
        qsort(object, num_objects, sizeof (int), compare_int);
        memset(used, 0, num_objects);
        length_goal = sum / 4;
        printf("%s\n", (sum % 4 == 0 && can_create_subset(0, 4, 0) ? "yes" : "no"));
    }
    return 0;
}
