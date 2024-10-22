/* 10534
 * Wavio Sequence
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NUMBERS 10000
#define MAX_TYPES 2

typedef enum {
    INCREASING,
    DECREASING
} type_t;

typedef struct number_s {
    int length[MAX_TYPES];
    int value;
} number_t, *number_p;

number_t number[MAX_NUMBERS];
number_p sequence[MAX_NUMBERS];
int num_numbers;

#define MIN(x, y) ((x) < (y) ? (x) : (y))

/* Calculate the longest increasing sequence length for each number */
void calculate_longest_length(type_t type) {
    int i, length, inc;
    for (i = (type == INCREASING ? 0 : num_numbers - 1), inc = (type == INCREASING ? 1 : -1),
            length = 0; (type == INCREASING && i < num_numbers) || (type == DECREASING && i >= 0);
            i += inc) {
        int start = 0, end = length, middle;
        while (start < end) {
            middle = (start + end) / 2;
            if (number[i].value > sequence[middle]->value) {
                start = middle + 1;
            }
            else {
                end = middle;
            }
        }
        number[i].length[type] = start;
        sequence[start] = &number[i];
        if (start == length) {
            length++;
        }
    }
}

/* Main function */
int main() {
    while (scanf("%d", &num_numbers) != EOF) {
        int i, maximum;
        for (i = 0; i < num_numbers; i++) {
            assert(scanf("%d", &number[i].value) != EOF);
        }
        calculate_longest_length(INCREASING);
        calculate_longest_length(DECREASING);
        for (i = 0, maximum = 0; i < num_numbers; i++) {
            int wavio = 2 * MIN(number[i].length[INCREASING], number[i].length[DECREASING]) + 1;
            if (wavio > maximum) {
                maximum = wavio;
            }
        }
        printf("%d\n", maximum);
    }
    return 0;
}
