/*
 * 259
 * Software Allocation
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define NUM_MACHINES 10
#define MAX_TASKS (NUM_MACHINES)
#define NUM_DIFFERENT_TASKS 26
#define MACHINE_SET (1 << NUM_MACHINES)
#define COMPLETE_MACHINE_SET (MACHINE_SET - 1)

#define INPUT_SIZE 80

typedef struct {
    char id;
    int requisitions;
    char machine[NUM_MACHINES];
    int num_machines;
} task_description_t;

task_description_t description[NUM_DIFFERENT_TASKS];
int total_descriptions;

int task[MAX_TASKS];
int num_tasks;

typedef struct {
    char machine;
    unsigned int remaining_machines;
} choice_t;
choice_t schedule[MAX_TASKS][MACHINE_SET];


/* Read data and return true if there will be anoter data, false otherwise */
int read_data(char *line) {
    num_tasks = 0;
    total_descriptions = 0;

    while (fgets(line, INPUT_SIZE, stdin) != NULL) {
        char *data;
        int i;
        if (line[0] == '\n') {
            return 1;
        }

        description[total_descriptions].id = line[0];
        description[total_descriptions].requisitions = line[1] - '0';
        description[total_descriptions].num_machines = 0;
        for (i = 0; i < description[total_descriptions].requisitions; i++) {
            if (num_tasks < MAX_TASKS) {
                task[num_tasks] = total_descriptions;
            }
            num_tasks++;
        } 
        
        data = line + 3;
        for (i = 0; data[i] != ';'; i++) {
            description[total_descriptions].machine[i] = data[i];
        }
        description[total_descriptions].num_machines = i;        
        total_descriptions++;
    }
    return 0;
}


/* Determine if a task can be assigned to a computer given a set of available computer */
#define NO_MACHINE '!'
int is_there_assignement(int t, int set) {
    int d;
    int possible = 0;

    for (d = 0; !possible && d < description[task[t]].num_machines; d++) {
        int comp = 1 << (description[task[t]].machine[d] - '0');
        int comp_free = set & comp;

        if (comp_free) {
            int new_set = set & (~ comp);
            possible = (t == 0 || 
                    (schedule[t - 1][new_set].machine != 0 ? 
                        schedule[t - 1][new_set].machine != NO_MACHINE: 
                        is_there_assignement(t - 1, new_set)));
            if (possible) {
                schedule[t][set].machine = description[task[t]].machine[d];
                schedule[t][set].remaining_machines = new_set;
            }
        }
    }
    if (!possible) {
        schedule[t][set].machine = NO_MACHINE;
    }
    return possible;
}


/* Reconsctruct computer allocation and print them */
void reconstruct_allocation_and_print() {
    static char allocation[NUM_MACHINES];
    int set = COMPLETE_MACHINE_SET;
    int i;

    memset(allocation, '_', sizeof (char) * NUM_MACHINES);
    for (i = num_tasks - 1; i >= 0; i--) {
        char computer = schedule[i][set].machine;
        allocation[computer - '0'] = description[task[i]].id;
        set = schedule[i][set].remaining_machines;
    }

    for (i = 0; i < NUM_MACHINES; i++) {
        printf("%c", allocation[i]);
    }
    printf("\n");    
}


/* Main function */
int main() {
    char line[INPUT_SIZE];
    int more_data = 1;
    
    while (more_data) {
        more_data = read_data(line);
        if (num_tasks > MAX_TASKS) {
            printf("!\n");
        }
        else {
            memset(schedule, 0, sizeof (choice_t) * MAX_TASKS * MACHINE_SET);
            if (!is_there_assignement(num_tasks - 1, COMPLETE_MACHINE_SET)) {
                printf("!\n");
            }
            else {
                reconstruct_allocation_and_print();
            }
        }
    }
    return 0;
}
