/*
 * 10138
 * CDVII
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_TAXES 24
#define MAX_VEHICLE_NAME 25
#define MAX_PHOTO_RECORDS 1000
#define MAX_NUMBER_CARS MAX_PHOTO_RECORDS
#define MAX_LINE_SIZE 1000

typedef enum {
    ENTER,
    EXIT
} action_t;

typedef struct {
    char plate[MAX_VEHICLE_NAME];
    int total_cost;
    int start_point, charge_index;
} car_t;
car_t car[MAX_NUMBER_CARS];
int num_cars;

typedef struct {
    char plate[MAX_VEHICLE_NAME];
    long timestamp;
    int charge_index;
    int kilometer;
    action_t action;
} photo_t;
photo_t photo[MAX_PHOTO_RECORDS];
int num_photos;

int charge[MAX_TAXES];


/* Find car index or add new car using binary search */
int find_or_add_car(char *plate) {
    int start, end, middle, found;
    start = 0;
    end = num_cars;
    middle = -1;
    found = 0;

    while (!found && start < end) {
        int comparison;
        middle = (start + end) / 2;
        comparison = strcmp(plate, car[middle].plate);
        found = (comparison == 0);
        if (comparison < 0) {
            end = middle;
        }
        else if (comparison > 0) {
            start = middle + 1;
        }
    }

    if (found) {
        return middle;
    }
    else {
        for (end = num_cars; end > start; end--) {
            car[end] = car[end - 1];
        }
        num_cars++;
        strcpy(car[start].plate, plate);
        car[start].total_cost = 0;
        car[start].charge_index = -1;
        return start;
    }
}


/* Read test data */
#define MINUTES_IN_HOUR (60)
#define MINUTES_IN_DAY (24 * MINUTES_IN_HOUR)
#define MINUTES_IN_MONTH (30 * MINUTES_IN_DAY)
void read_data() {
    char line[MAX_LINE_SIZE];
    char *input;
    int i;

    assert(fgets(line, MAX_LINE_SIZE, stdin) != NULL);
    input = line;
    for (i = 0; i < MAX_TAXES; i++) {
        charge[i] = strtol(input, &input, 0);
    }

    num_photos = 0;
    num_cars = 0;

    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL) {
        char action[MAX_VEHICLE_NAME];
        int month, day, hour, minute;
        if (line[0] == '\n') {
            break;
        }

        sscanf(line, "%s %d:%d:%d:%d %s %d", photo[num_photos].plate, &month, &day, &hour,
                &minute, action, &photo[num_photos].kilometer);
        photo[num_photos].timestamp = minute + hour * MINUTES_IN_HOUR + 
                day * MINUTES_IN_DAY + month * MINUTES_IN_MONTH;
        photo[num_photos].charge_index = hour;
        photo[num_photos].action = (strcmp(action, "enter") == 0 ? ENTER : EXIT);
        find_or_add_car(photo[num_photos].plate);
        num_photos++;
    }        
}


/* Sort photos by timestamp */
int compate_photo(const void *a, const void *b) {
    return ((photo_t *) a)->timestamp - ((photo_t *) b)->timestamp;
}


/* Count costs for each car trip */
void count_costs() {
    int i;
    qsort(photo, num_photos, sizeof (photo_t), compate_photo);
    for (i = 0; i < num_photos; i++) {
        int c = find_or_add_car(photo[i].plate);
        switch (photo[i].action) {
            case ENTER:
                car[c].charge_index = photo[i].charge_index;
                car[c].start_point = photo[i].kilometer;
                break;
            case EXIT:
                if (car[c].charge_index != -1) {
                    car[c].total_cost += abs(car[c].start_point - photo[i].kilometer) * 
                            charge[car[c].charge_index] + 100;
                    car[c].charge_index = -1;
                }
        }
    }

    for (i = 0; i < num_cars; i++) {
        if (car[i].total_cost > 0) {
            car[i].total_cost += 200;
        }
    }
}


/* Print report */
void print_bill_report() {
    int i;
    for (i = 0; i < num_cars; i++) {
        if (car[i].total_cost > 0) {
            printf("%s $%d.%02d\n", car[i].plate, car[i].total_cost / 100, car[i].total_cost % 100);
        }
    }
}


/* Main function */
int main() {
    int num_tests, test;
    char line[MAX_LINE_SIZE];

    assert(fgets(line, MAX_LINE_SIZE, stdin) != NULL);
    num_tests = atoi(line);
    for (test = 0; test < num_tests; test++) {
        (test == 0 ? assert(fgets(line, MAX_LINE_SIZE, stdin) != NULL) : (void) printf("\n"));
        read_data();
        count_costs();
        print_bill_report();
    }

    return 0;
}
