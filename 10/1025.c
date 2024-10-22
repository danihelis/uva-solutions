/* 1025
 * A Spy in the Metro
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TIME        200
#define MAX_STATIONS    50
#define MAX_TRAINS      50
#define INFINITY        10000

typedef struct {
    int origin, departing, arrival;
} train_t;

typedef struct {
    train_t train[MAX_TRAINS * 2];
    int num_trains;
} station_t;

station_t station[MAX_STATIONS];
int waiting[MAX_TIME + 1][MAX_STATIONS];
int num_stations, time_limit;

/* Comprare trains arriving in a station by time of arrival */
int compare(const void *a, const void *b) {
    train_t *pa = (train_t *) a, *pb = (train_t *) b;
    return pa->arrival - pb->arrival;
}

/* Read and create train schedules */
void read_train_schedules() {
    int interval[MAX_STATIONS], num_trains, direction, time, i, t;
    for (i = 0; i < num_stations; i++) {
        station_t *s = &station[i];
        s->num_trains = 0;
        if (i < num_stations - 1) assert(scanf("%d", &interval[i]) == 1);
    }
    for (direction = 1; direction >= -1; direction -= 2) {
        assert(scanf("%d", &num_trains) == 1);
        for (t = 0; t < num_trains; t++) {
            int current = direction > 0 ? 0 : num_stations - 1,
                final = direction > 0 ? num_stations - 1 : 0;
            assert(scanf("%d", &time) == 1);
            while (current != final) {
                int next = current + direction;
                station_t *s = &station[next];
                train_t *train = &s->train[s->num_trains];
                train->departing = time;
                time += interval[direction > 0 ? current : next];
                if (time > time_limit) break;
                train->origin = current;
                train->arrival = time;
                s->num_trains++;
                current = next;
            }
        }
    }
    for (i = 0; i < num_stations; i++) {
        station_t *s = &station[i];
        qsort(s->train, s->num_trains, sizeof (train_t), compare);
    }
}

/* Compute lowest waiting time for each station and timestamp */
void compute_lowest_waiting() {
    int time, i, j, w;
    for (time = 0; time <= time_limit; time++) {
        for (i = 0; i < num_stations; i++) {
            if (time == 0) waiting[0][i] = i == 0 ? 0 : INFINITY;
            else {
                station_t *s = &station[i];
                waiting[time][i] = waiting[time - 1][i] + 1;
                for (j = 0; j < s->num_trains; j++) {
                    train_t *t = &s->train[j];
                    if (t->arrival > time) break;
                    w = time - t->arrival + waiting[t->departing][t->origin];
                    if (w < waiting[time][i]) waiting[time][i] = w;
                }
            }
        }
    }
}

/* Main function */
int main() {
    int test = 0, answer;
    while (scanf("%d", &num_stations) == 1 && num_stations > 0) {
        assert(scanf("%d", &time_limit) == 1);
        read_train_schedules();
        compute_lowest_waiting();
        answer = waiting[time_limit][num_stations - 1];
        printf("Case Number %d: ", ++test);
        if (answer > time_limit) printf("impossible\n");
        else printf("%d\n", answer);        
    }
    return EXIT_SUCCESS;
}
