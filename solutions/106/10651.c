/* 10651
 * Pebble Solitaire
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_PEBBLES 12
#define MAX_STRING  (MAX_PEBBLES + 2)
#define MAX_SETS    (1 << MAX_PEBBLES)
#define UNDEFINED   -1

#define HAS(s, i)   ((s) & (1 << (i)))

char solution[MAX_SETS];

/* Convert a string representation into set numeric value */
int pebbles_to_set(char *pebbles) {
    int i, set = 0;
    for (i = 0; i < MAX_PEBBLES; i++) {
        if (pebbles[i] == 'o') {
            set |= (1 << i);
        }
    }
    return set;
}

/* Get minimum number of pebbles from configuration set */
int get_minimum(int set) {
    assert(set < MAX_SETS);
    if (solution[set] != UNDEFINED) {
        return solution[set];
    }
    else {
        int i, num_pebbles = 0, minimum = MAX_PEBBLES;
        for (i = 0; i < MAX_PEBBLES; i++) {
            if (HAS(set, i)) {
                num_pebbles++;
                if (i >= 2 && HAS(set, i - 1) && !HAS(set, i - 2)) {
                    int new_set = (set | (1 << (i - 2))) ^ ((1 << (i - 1)) | (1 << i));
                    int sol = get_minimum(new_set);
                    if (sol < minimum) {
                        minimum = sol;
                    }
                }
                if (i < MAX_PEBBLES - 2 && HAS(set, i + 1) && !HAS(set, i + 2)) {
                    int new_set = (set | (1 << (i + 2))) ^ ((1 << (i + 1)) | (1 << i));
                    int sol = get_minimum(new_set);
                    if (sol < minimum) {
                        minimum = sol;
                    }
                }
            }
        }
        if (num_pebbles < minimum) {
            minimum = num_pebbles;
        }
        solution[set] = minimum;
        return minimum;
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    memset(solution, UNDEFINED, MAX_SETS);
    for (; num_tests > 0; num_tests--) {
        char input[MAX_STRING];
        assert(scanf(" %s", input) != EOF);
        printf("%d\n", get_minimum(pebbles_to_set(input)));
    }
    return 0;
}
