/*
 * 247
 * Calling Circles
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NAMES 25
#define MAX_NAME_SIZE 30

typedef struct {
    char name[MAX_NAME_SIZE];
    int circle;
} caller_t;

caller_t caller[MAX_NAMES];
int num_callers;

char call[MAX_NAMES][MAX_NAMES];

typedef struct {
    int person[MAX_NAMES];
    int num_people;
} circle_t;

circle_t circle[MAX_NAMES];
int num_circles;


/* Get name index or add name to list */
int get_caller_index(char *name) {
    int i;
    for (i = 0; i < num_callers; i++) {
        if (strcmp(name, caller[i].name) == 0) {
            return i;
        }
    }
    strcpy(caller[num_callers].name, name);
    caller[num_callers].circle = -1;
    num_callers++;
    return (num_callers - 1);
}


/* Read data from input */
void read_data(int num_calls) {
    char person_name[2][MAX_NAME_SIZE];
    int person_index[2];
    int i;

    num_callers = 0;
    memset(call, 0, sizeof (char) * MAX_NAMES * MAX_NAMES);
    for (i = 0; i < num_calls; i++) {
        assert(scanf("%s%s", person_name[0], person_name[1]) == 2);
        person_index[0] = get_caller_index(person_name[0]);
        person_index[1] = get_caller_index(person_name[1]);
        call[person_index[0]][person_index[1]] = 1;
    }
}


/* Find circles by determinig all reachable paths from each node and grouping them */
void find_circles() {
    int i, j, k;

    /* Floyd-Warshall, surely there is one faster */
    for (k = 0; k < num_callers; k++) {
        for (i = 0; i < num_callers; i++) {
            for (j = 0; j < num_callers; j++) {
                if (call[i][k] && call[k][j]) {
                    call[i][j] = 1;
                }
            }
        }
    }

    num_circles = 0;
    for (i = 0; i < num_callers; i++) {
        if (caller[i].circle == -1) {
            int people = 1;
            caller[i].circle = num_circles;
            circle[num_circles].person[0] = i;

            for (j = 0; j < num_callers; j++) {
                if (i != j && call[i][j] && call[j][i]) {
                    caller[j].circle = num_circles;
                    circle[num_circles].person[people++] = j;
                }
            }            
            circle[num_circles++].num_people = people;
        }
    }
}


/* Print circles */
void print_circles(int set) {
    int i;
    printf("Calling circles for data set %d:\n", set);
    for (i = 0; i < num_circles; i++) {
        int n;
        for (n = 0; n < circle[i].num_people; n++) {
            printf("%s%s", caller[circle[i].person[n]].name, 
                    (n < circle[i].num_people - 1 ? ", " : "\n"));
        }
    }
}



/* Main function */
int main() {
    int num_callers, num_calls, data_set;
    data_set = 1;

    while (scanf("%d %d", &num_callers, &num_calls) != EOF) {
        if (num_callers == 0 && num_calls == 0) {
            break;
        }
        if (data_set > 1) {
            printf("\n");
        }
        read_data(num_calls);        
        find_circles();
        print_circles(data_set);
        data_set++;
    }

    return 0;
}
