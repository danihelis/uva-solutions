/*
 * 10191
 * Longest Nap
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TASKS 101
typedef struct {
    int start, end, duration;
} activity_t;
activity_t task[MAX_TASKS];
int num_tasks;
activity_t nap[MAX_TASKS];
int num_naps;


/* Compare by start time */
int compare_start_time(const void *a, const void *b) {
    return ((activity_t *) a)->start - ((activity_t *) b)->start;
}


/* Compare by duration time */
int compare_duration_time(const void *a, const void *b) {
    if (((activity_t *) b)->duration == ((activity_t *) a)->duration) {
        return ((activity_t *) a)->start - ((activity_t *) b)->start;
    }
    return ((activity_t *) b)->duration - ((activity_t *) a)->duration;
}


/* Find all naps */
#define END_OF_DAY (8 * 60)
void find_naps() {
    int t;
    int end = 0;
    num_naps = 0;
    for (t = 0; t < num_tasks; t++) {
        if (end < task[t].start) {
            nap[num_naps].start = end;
            nap[num_naps].end = task[t].start;
            nap[num_naps].duration = nap[num_naps].end - nap[num_naps].start;
            num_naps++;
            end = task[t].start;
        }
        if (task[t].end > end) {
            end = task[t].end;
        }
    }
    if (end < END_OF_DAY) {
        nap[num_naps].start = end;
        nap[num_naps].end = END_OF_DAY;
        nap[num_naps].duration = nap[num_naps].end - nap[num_naps].start;
        num_naps++;
    }
}


/* Output longest nap */
void output_longest_nap() {
    find_naps();
    qsort(nap, num_naps, sizeof (activity_t), compare_duration_time);
    printf("the longest nap starts at %d:%02d and will last for ", 
            (10 + (nap[0].start / 60)), (nap[0].start % 60));
    if (nap[0].duration >= 60) {
        printf("%d hours and ", (nap[0].duration / 60));
    }
    printf("%d minutes.\n", (nap[0].duration % 60));
}


/* Read tasks of day */
#define MAX_INPUT 1000
void read_taks() {
    char input[MAX_INPUT];
    int t;
    for (t = 0; t < num_tasks; t++) {
        char *line;
        assert(fgets(input, MAX_INPUT, stdin) != NULL);
        line = input;
        line[2] = '\0';
        task[t].start = (atoi(line) - 10) * 60;
        line += 3;
        line[2] = '\0';
        task[t].start += atoi(line);
        line += 3;
        line[2] = '\0';
        task[t].end = (atoi(line) - 10) * 60;
        line += 3;
        line[2] = '\0';
        task[t].end += atoi(line);
    }
    qsort(task, num_tasks, sizeof (activity_t), compare_start_time);
}


/* Main function */
int main() {
    char input[MAX_INPUT];
    int day = 1;
    while (fgets(input, MAX_INPUT, stdin) != NULL) {
        if (input[0] == '\n') {
            break;
        }
        num_tasks = atoi(input);
        read_taks();
        printf("Day #%d: ", day++);
        output_longest_nap();
    }
    return 0;
}
