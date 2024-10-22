/*
 * 10037
 * Bridge
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>


#define MAX_PEOPLE 1000
int travel[MAX_PEOPLE];
int num_people;

typedef struct {
    int going[2], returning;
} triple_t;
triple_t solution[MAX_PEOPLE];


/* Utilities */
#define DUAL_PASS(slow, slower, back, i, time) \
    do { \
        solution[(i)].going[0] = travel[(slow)]; \
        solution[(i)].going[1] = travel[(slower)]; \
        solution[(i)].returning = travel[(back)]; \
        (i)++; \
        (time) += travel[(slower)] + travel[(back)]; \
    } while (0)

#define FAST_PASS(fast, slow, ind, time) DUAL_PASS(fast, slow, fast, ind, time)

#define JUST_GO(fast, slow, i, time) \
    do { \
        solution[(i)].going[0] = travel[(fast)]; \
        solution[(i)].going[1] = travel[(slow)]; \
        solution[(i)].returning = 0; \
        (i)++; \
        (time) += travel[(slow)]; \
    } while (0)


/* Compare time of travel for sorting them */
int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}


/* Calculate best time to traverse the bridge */
#define ALTERNATIVE 1
int best_traverse() {
    int fastest, heaviest, heavy;
    char alternative_passed = 0;
    int index = 0;
    int total_time = 0;

    qsort(travel, num_people, sizeof (int), compare);
    fastest = 0;
    heaviest = num_people - 1;

    /* This will iterate until two or three people are left behind, or one less if the "alternative" passed */
    while (heaviest >= 3) {
        heavy = heaviest - 1;
        if (!alternative_passed) {
            FAST_PASS(fastest, ALTERNATIVE, index, total_time);
            alternative_passed = 1;
        }
        if ((travel[heavy] + travel[fastest] > 2 * travel[ALTERNATIVE])) {
            DUAL_PASS(heavy, heaviest, ALTERNATIVE, index, total_time);
            alternative_passed = 0;
        }
        else {
            FAST_PASS(fastest, heaviest, index, total_time);
            FAST_PASS(fastest, heavy, index, total_time);
        }
        heaviest -= 2;
    }

    assert(heaviest == 1 || heaviest == 2);
    if (heaviest == 2) {
        if (!alternative_passed) {
            FAST_PASS(fastest, ALTERNATIVE, index, total_time);
        }
        JUST_GO(fastest, heaviest, index, total_time);
    }
    else {
        if (!alternative_passed) {
            JUST_GO(fastest, ALTERNATIVE, index, total_time);
        }
        else {
            solution[index].returning = -1;
            total_time -= travel[fastest];
        }
    }

    assert(index == num_people - 1);
    return total_time;
}


/* Calculate and print solution */
void print_solution() {
    if (num_people == 1) {
        printf("%d\n%d\n", travel[0], travel[0]);
    }
    else {
        int i;
        printf("%d\n", best_traverse());
        for (i = 0; i < num_people - 1; i++) {
            printf("%d %d\n", solution[i].going[0], solution[i].going[1]);
            if (i < num_people - 2) {
                printf("%d\n", solution[i].returning);
            }
        }
    }
}


/* Main function */
int main() {
    int num_cases, cur_case;

    assert(scanf("%d", &num_cases) != EOF);
    for (cur_case = 0; cur_case < num_cases; cur_case++) {
        int person;
        if (cur_case > 0) {
            printf("\n");
        }
        
        assert(scanf("%d", &num_people) != EOF);
        for (person = 0; person < num_people; person++) {
            assert(scanf("%d", &travel[person]) != EOF);
        }
        print_solution();
    }

    return 0;
}
