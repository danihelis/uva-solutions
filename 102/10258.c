/* 10258
 * Contest Scoreboard
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_CONTESTANTS 100
#define MAX_PROBLEMS 9
#define MAX_INPUT 100

typedef struct {
    char solved[MAX_PROBLEMS];
    int incorrect[MAX_PROBLEMS];
    int problems, time, id;
} contestant_t, *contestant_p;

contestant_t contestant[MAX_CONTESTANTS];

/* Compare two contestants in order to sort */
#define NONZERO(x) (x == 0 ? MAX_CONTESTANTS * 2 : x)
int compare(const void *a, const void *b) {
    contestant_p x = (contestant_p) a, y = (contestant_p) b;
    if (x->problems != y->problems) {
        return y->problems - x->problems;
    }
    if (x->time != y->time) {
        return x->time - y->time;
    }
    return NONZERO(x->id) - NONZERO(y->id);
}

/* Main function */
int main() {
    int i = -1, tests;
    char input[MAX_INPUT];
    assert(fgets(input, MAX_INPUT, stdin) != NULL);
    tests = atoi(input);
    assert(fgets(input, MAX_INPUT, stdin) != NULL);
    assert(input[0] == '\n');
    for (; tests > 0; tests--) {
        memset(contestant, 0, MAX_CONTESTANTS * sizeof (contestant_t));
        while (fgets(input, MAX_INPUT, stdin) != NULL) {
            int id, prob, time;
            char result;
            if (input[0] == '\n') {
                break;
            }
            assert(sscanf(input, "%d %d %d %c", &id, &prob, &time, &result) == 4);
            id--, prob--;
            contestant[id].id = id + 1;
            if (result == 'C' && !contestant[id].solved[prob]) {
                contestant[id].solved[prob] = 1;
                contestant[id].problems++;
                contestant[id].time += time + contestant[id].incorrect[prob] * 20;
            }
            else if (result == 'I' && !contestant[id].solved[prob]) {
                contestant[id].incorrect[prob]++;
            }
        }
        qsort(contestant, MAX_CONTESTANTS, sizeof (contestant_t), compare);
        if (i >= 0) {
            printf("\n");
        }
        for (i = 0; i < MAX_CONTESTANTS && contestant[i].id != 0; i++) {
            printf("%d %d %d\n", contestant[i].id, contestant[i].problems, contestant[i].time);
        }
    }
    return 0;
}
