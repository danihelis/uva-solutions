/* 481
 * What Goes Up
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SIZE 1000000

typedef struct value_s {
    struct value_s *next;
    int value;
} value_t, *value_p;

value_t vector[MAX_SIZE];
value_p sequence[MAX_SIZE];
int length, maximum;

/* Main function */
int main() {
    int solution[MAX_SIZE], i;
    value_p best;
    maximum = 0, length = 0;
    while (scanf("%d", &vector[length].value) != EOF) {
        assert(length < MAX_SIZE);
        for (i = maximum - 1; i >= 0 && vector[length].value <= sequence[i]->value; i--)
            ;
        sequence[i + 1] = &vector[length];
        vector[length].next = (i >= 0 ? sequence[i] : NULL);
        if (i == maximum - 1) {
            maximum++;
        }
        length++;
    }
    for (best = sequence[maximum - 1], i = maximum - 1; best != NULL; i--, best = best->next) {
        assert(i >= 0);
        solution[i] = best->value;
    }
    assert(i < 0);
    printf("%d\n-\n", maximum);
    for (i = 0; i < maximum; i++) {
        printf("%d\n", solution[i]);
    }
    return 0;
}
